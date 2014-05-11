%   File : testRender.m
% Author : Josh Gleason
%   Date : 05/09/14
% This script is meant to perform simple mesh render based on a small artificial sinc function
% dataset. Tests the error computation presented in "Lindstrom et al. Terrain
% implification Simplified (2002)" in Section C. And renders a triangle mesh using the
% method described in Section D. This script favors readability over speed and makes
% no attempts to optimize calculations.

function [p, z, e, einc, r]=testRender() 
  %% Input parameters
    % width/height of regular grid (Must be of the form 2^n+1)
    sz = 2^4+1;
    % pixel error threshold based on 60 degree FOV and 640 pixel screen resolution
    tau=1;
    % set a camera position
    camPos = [0,-16,8];
  
  %% Initialize all the variables that are needed for this calculation.
    % generate a sinc function for sample dataset in a regular 17 x 17 grid
    z = gensinc(sz);
    % active vertices (corners are active by default)
    v = zeros(sz,sz); v(1,1) = 1; v(1,sz) = 1; v(sz,1) = 1; v(sz,sz) = 1;
    % world space error
    einc = zeros(sz,sz);
    % monatonically increasing error (in terms of DAG traversal)
    e = zeros(sz,sz);
    % screen space error (doesn't actually need to be initialized here)
    p = zeros(sz,sz);
    % radius of bounding ball used in screen space error calculation
    r = zeros(sz,sz);
    % This is the root nodes position
    root = [(sz-1)/2,(sz-1)/2];
    % this will be the Directed Acyclic graph's adjacency matrix
    DAG = zeros(sz*sz,sz*sz);

  %% Preprocessing on dataset
    % These values would be stored as metadata in the file containing the heightmap.
    
    % I need to build the DAG of the scene. The center of the mesh is the parent. Based on
    % Section A in the paper. See Figure 2 for help understanding graph topology.
    DAG = addchildren(DAG, root, 1);
    % compute radius of bounding balls using Equation 3.
    r = boundingBall(DAG, root, 1, r);
    % compute actual incremental world space error using Equation 4 (The maximum world space
    % error metric from Equation 5 could also be used in place of this metric).
    einc = computeEInc(DAG, z, root, 1, einc);
    % compute monatonically increasing world space error (in terms that e_ancestor <= e_node)
    % using Equation 2.
    e = computeE(DAG, einc, root, 1, e);

  %% Would need to be computed every frame
    % Compute screen space error using isotropic projection (simpler than perspective)
    % using Equation 7 (Optionally I could be using perspective screen space error described
    % in Equation 10). It should be noted that this value doesn't need to be computed for
    % every node, if a parent node is deactivated (p <= tau) then I know because of the
    % monatonic property of this metric, that all the children will also be deactivated.
    p = computePIsotropic(e, r, camPos, z);
    % Filter vertices with screen space error above pixel threshold (tau). The smaller tau is
    % the more vertices activated based on Equation 8 or 11.
    v = getActiveVerts(p, tau, v);
    % Compute the triangle strip vertices using the method described in Section D.
    tstrip=meshrefine(v);
    
    %% TODO: Perform View Frustum Culling (Section E)
  
  %& Show results
    % Plot the active vertices in top-down view
    figure(1);
    plotVerts(v);
    % Plot the mesh as a 3d wireframe (pretty slow because hold on slows octave down so much)
    figure(2);
    plotTStrip(tstrip,z);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%               Compute Bounding Balls (Lateral World Space Error)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Bounding ball's are described in Section B and are computed using Equation 3.
% There are two goals of the bounding balls.
%
% The first is to threshold when a screen space error even needs to be computed.
% Basically, if your camera is within the bounding ball of a vertex, then that vertex
% must be activated.
%
% The second is the ensure that screen space error is monatonically increasing
% from parent to child. This metric complements the world space height error metric
% by ensuring that both vertical (z) and lateral (x-y) errors are considered when
% computing screen space errors.
%
% The only property of a bounding ball is that the bounding ball of a vertex always
% encompasses the bounding balls of that vertex's decendents. This enforces the
% nesting property which allows valid vertex activation configurations.
%
% One great thing about using a regular grid is that the x-y error is constant for
% a given level of the DAG. This means that the bounding ball radii will only need
% to be computed upon initialization of a program.

% Compute radius of bounding balls in DAG using Equation 3
function r=boundingBall(DAG, node, level, r)
  sz = numel(DAG)^0.25;
  maxLevel = log2(sz-1)*2;
  if level == maxLevel % leaf
    r(node(1)+1, node(2)+1) = 0;
  else
    cpos = getChildren(DAG, node);
    for i=1:numel(cpos)/2
      cnode = cpos(i,:);
      if r(cnode(1)+1, cnode(2)+1) == 0
        r=boundingBall(DAG, cnode, level+1, r);
      end
              
      % recurse down the tree to determine value of r. This recursion visits
      % the lowest nodes first. Everything below should already have a validPos
      % value for r. The bbRadius does not modify r it simply returns the value
      % of r(node)
      % POSSIBLE OPTIMIZATION FROM PAPER, IT APPEARS THAT I MAY ONLY NEED TO VISIT
      % THE CHILD NODES TO ENSURE IVE FOUND THE MAXIMUM
      r(node(1)+1, node(2)+1) = bbRadius(DAG, node, cnode, level+1, r, 0);
      
    end
  end
end

% Used to compute the "otherwise" part of Equation 3. Used by boundingBall function
function maxval=bbRadius(DAG, inode, node, level, r, maxval)
  sz = numel(DAG)^0.25;
  maxLevel = log2(sz-1)*2;
  % last level must be included
  if level <= maxLevel
    % compute the distance from inode to node (Equation 3 in paper)
    dist = norm(node-inode) + r(node(1)+1, node(2)+1);
    maxval = max([dist maxval]);
    cpos = getChildren(DAG, node);
    for i=1:numel(cpos)/2
      cnode = cpos(i,:);
      maxval = bbRadius(DAG, inode, cnode, level+1, r, maxval);
    end
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                        World Space Height Error Metrics
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% World space z-error measures the amount of elevation (z-axis) error introduced by NOT
% activating a vertex. i.e. This answers the question. If you were to remove this vertex
% from the mesh, how much elevation error would be introduced in world space?
%
% This metric is view-independent and can therefore be pre-computed and stored as metadata
% in the heightmap.
%
% There are two metrics presented in the paper by Lindstrom, incremental world space
% error and maximum world space error. Incremental error (einc) computes only the error
% introduced by removing a vertex, but ignores the potentially greater error that could
% be caused by removing the decendents of this vertex. A decendent can not be activated
% without it's parent being activated, so this could potentially cause visible errors
% in the mesh where there are high frequency changes in the terrain (like a spike or cliff).
% The Maximum error (emax) examines the decendents of the vertex and determines the
% maximumum height error that would be introduced into the mesh by removing the vertex.
% The emax metric is always at least as great as the einc metric and therefore will cause
% at least as many active vertices as einc would, but high frequency changes in terrain
% will keep the true screen space error less-than or equal-to the desired screen space
% error.
%
% More about computing emax and emin.
%
% A node p_j has two triangles which it bisects. The parents of p_j
% being p_i1 and p_i2 make those triangles t1=t(p_i1, p_j) and t2=t(p_i2, p_j)
%
%  (Imagine angle(ABC) and angle(CDA) are 90 degrees.)
%
%        p_i1 ---> B   
%                /   \
%              /  t1   \
%            /           \  
%  v_l --> A-------E-------C <-- v_r
%            \           /
%              \  t2   /
%                \   /
%                  D  <---- p_i2
%       
% The "E" vertex in the center of the diamond is p_j. t1 = ABC = t(B,E)
% and t2 = ACD = t(D,E). See Figure 1 and Section A for more information on
% longest edge bisection.

% In the paper, D_{i,j} is contains all descendents of i reached by recursive
% bisection of triangle t(i,j). i.e. Only recurse down paths of cl and cr
% (using the cl and cr functions) which are the left and right children of
% node i which bisect the two triangles created when j bisects i.
%
% Notice that the subscripts in the error term (delta hat) differ between
% Equation 4 and Equation 5. Equation 4 determines the difference added by
% bisecting only the first cut of the triangle making the z_t just the average
% z of z(v_l) and z(v_r). In Equation 5 I need the actual z value of the triangle
% at multiple places in t1 and t2 (not necessarily on the bisecting edge or any
% edge for that matter). This means we'll want to use homogenous coordinatates
% to determine the z value at any point inside the triangle.
%
% Here's an example of what emax actually represents. Consider the diagram below
% showing a mesh with triangles drawn at a resolution of 2 levels courser than the
% maximum resolution.
%
%                 \   /
%                   B
%                 /   \
%               /       \
%             /           \
%           F       K       G
%         /                   \
%       /                       \
% \   /                           \   /   
%   A-------J-------E-------L-------C
% /   \                           /   \
%       \                       /
%         \                   /
%           I       M       H
%             \           /
%               \       /
%                 \   /
%                   D
%                 /   \
%
%  emax(E) represents the maximum height error introduced into the scene by NOT activating
%  vertex E. Well the first thing to consider would be that not activating E would
%  at least introduce the error delta_{E, ABC} = |z(E)-zABC(E)| = delta_{E,ACD} = |z(E)-zACD(E)|
%  where zABC(E) is the z value of the triangle ABC at E and zACD(E) is the z value of
%  the triangle ACD at E. This is as far as the incremental error metric (einc) computes.
%  However, we know that without activating E, vertices F, K, G, J, L, I, M, H also can't be
%  activated (parent/child relationship) which could possibly introduce even more error
%  than what is computed by the incremental error error alone.
%  dF = delta_{F, ABC}
%  dK = delta_{K, ABC}
%  dG = delta_{G, ABC}
%  dJ = delta_{J, ABC}
%     = delta_{J, ACD}
%  dE = delta_{E, ABC}
%     = delta_{J, ACD}
%     = einc(E)
%  dL = delta_{L, ABC}
%     = delta_{L, ACD}
%  dI = delta_{I, ACD}
%  dM = delta_{M, ACD}
%  dH = delta_{H, ACD}
%
%  emax(E) = max(dF, dK, dG, dJ, dE, dL, dI, dM, dH)
%  Now, emax represents the true maximum height error introduced into the mesh by excluding
%  vertex E.         
%
%  Extended version of previous diagram showing a finer resolution around vertex F. (Also added
%  vertex N and other unlabeled vertices).
%
%   |             \   /
% --N-------x-------B       x       x
%   |             / | \
%   |           /   |   \
%   |         /     |     \
%   x       F       K       G       x
%   |     /         |         \
%   |   /           |           \
% \ | /             |             \   /   
%   A-------J-------E-------L-------C
% /   \             |             /   \
%       \           |           /
%         \         |         /
%   x       I       M       H       x
%             \     |     /
%               \   |   /
%                 \ | /
%   x       x       D       x       x
%                 /   \
%
%  Unfortunately, emax needs to traverse all the way down the tree for every node and can't easily be
%  computed incrementally using a bottom-up approach. Here's an example of why. The value emax(F)
%  isn't necessarily less-than or equal-to emax(E). This is because F bisects the triangles ANB and
%  BEA. Therefore triangle ANB needs to be considered when computing emax(F) but this area should
%  certainly not be considered when computing emax(E) because triangle ANB doesn't fall in either
%  triangle ABC or ACD. This is what is implied by the statement "einc and emax are not necessarily
%  nested" in the paragraph below Equation 5.
  
% Compute incremental world space error from Equation 5.
function emax = computeEMax(DAG, z, einc, node, level, emax)
  % TODO
  fprintf('emax function not yet implemented\n');
  emax = einc;
end

% Compute incremental world space error from Equation 4
function einc = computeEInc(DAG, z, node, level, einc)
  sz = numel(DAG)^0.25;
  % for 17x17 max level of tree is 8, for 9x9 its 6, for 5x5 its 4, etc...
  maxLevel = log2(sz-1)*2;
  if level < maxLevel
    % get children of node
    cpos = getChildren(DAG, node);
    % to find the z values of the left and right corners of the triangle,
    % first take the vector cnode-node then rotate it 90 degrees and -90
    % degrees. Add both vectors to cnode to find the position of the left
    % and right corners of the triangle defined by node and cnode.
    for i=1:(numel(cpos)/2)
      cnode = cpos(i,:);
      % node may have already been visited so check before wasting time
      if einc(cnode(1)+1, cnode(2)+1)==0
        % find the left and right sides of the triangle (find the edge being bisected)
        vec = cnode-node;
        vec090 = rotateVec(vec,90);
        vec270 = rotateVec(vec,270);
        posL = cnode + vec090;
        posR = cnode + vec270;
        zl = z(posL(1) +1, posL(2) +1);
        zr = z(posR(1) +1, posR(2) +1);
        zi = z(cnode(1)+1, cnode(2)+1);
        e = abs(zi - (zl+zr)/2);
        einc(cnode(1)+1, cnode(2)+1) = e;
        einc = computeEInc(DAG, z, cnode, level+1, einc);
      end
    end
  end
end

% Compute refined world space error using Equation 2. ehat is either einc or emax.
% This function just takes ehat and forces it to be monatonically decreasing from
% parent to child (i.e. a parent's error is always greater or equal to than a decendent).
% This is necessary to ensure nesting which is one of the necessary conditions to ensure
% that the screen space error will be monatonic. (The other condition is that the
% bounding balls are nested, see Section B).
function e = computeE(DAG, ehat, node, level, e)
  sz = numel(DAG)^0.25;
  maxLevel = log2(sz-1)*2;
  if level == maxLevel %leaf
    e(node(1)+1, node(2)+1) = ehat(node(1)+1, node(2)+1);
  else
    cpos = getChildren(DAG, node);
    for i=1:(numel(cpos)/2)
      cnode = cpos(i,:);
      % recurse all the way down the tree before comparing for maximum
      % if node has already been visited (which is possible because most
      % nodes have multiple parents) then ignore it.
      if e(cnode(1)+1, cnode(2)+1) == 0
        e = computeE(DAG, ehat, cnode, level+1, e);
      end
    end
    maxval = -1;
    % if e for children is larger than ehat for node then update e with
    % largest child value
    for i=1:(numel(cpos)/2)
      cnode = cpos(i,:);  
      % recurse all the way down the tree before comparing for maximum
      maxval = max([e(cnode(1)+1, cnode(2)+1), maxval]);
    end
    e(node(1)+1, node(2)+1) = max([e(node(1)+1, node(2)+1), maxval]);
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                           Directed Acyclic Graph (DAG)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% The Directed Acyclic Graph (DAG) is used to link nodes in a pyramid heirarchy. A
% parent node contains at most 4 children who are at a higher resolution in the grid.
% We can think of this DAG as a Quad-tree where some children are shared between nodes.
% The structure of the DAG is described in detail in Section A but I'll show an example
% which I think helps.
%
% Consider the following set of vertices where each vertex is equally spaced (top-down view).
% Note that the grid must be of width and height 2^n+1 where n is an integer.
%
% A   B   C   D   E
% 
% F   G   H   I   J
%
% K   L   M   N   O
%
% P   Q   R   S   T
%
% U   W   X   Y   Z
%
% The DAG would be as follows (displayed as a quad tree with some shared children)
%                                                             LEVEL
%              /----------+-----M-----+----------\              1
%             |           |           |           |
%             |           |           |           |
%   >-\   /---K---\   /---X---\   /---O---\   /---C-->          2
%      \ /         \ /         \ /         \ /
%       |           |           |           |
%   <-+-G-+-\   /-+-Q-+-\   /-+-S-+-\   /-+-I-+-\   /-<         3
%     |   |  \ /  |   |  \ /  |   |  \ /  |   |  \ /
%     |   |   |   |   |   |   |   |   |   |   |   |
%     B   F   L   P   W   R   Y   T   N   J   D   H             4
%
% This diagram is meant to convey the parent/child relationship like M is the parent of K, W, O and C.
% It doesn't convey the geometric relationship between parent and child. You can see this better in
% Figure 2 in the paper. Or the diagram below which shows the DAG's geometric topology.
%
%
%   LEVEL 1 -> 2          LEVEL 2 -> 3          LEVEL 3 -> 4
%
%         C          |          C          |      B       D    
%         ^          |          |          |      ^       ^    
%         |          |      G <-+-> I      |  F <-G-> H <-I-> J
%         |          |      ^       ^      |      v       v    
% K <-----M-----> O  |  K---+       +---O  |      L       N    
%         |          |      v       v      |      ^       ^    
%         |          |      Q <-+-> S      |  P <-Q-> R <-S-> T
%         v          |          |          |      v       v    
%         X          |          W          |      W       Y    
%
% Notice that a node may have multiple parents but at most 4 children
%   K is a parent of G and Q
%   C is a parent of I and G
%   G's parents are K and C
%
% With this structure, there is rule that, if a parent vertex is active in the mesh (i.e. at
% least one triangle is using the vertex), then all of it's children must also be active. This allows
% for a good structure of spliting the mesh and computing error metrics.
%
% Be mindful that we want to prevent T-juctions in the mesh which could cause holes. This is enforced
% by ensuring that error metrics are nested. I.E. error of a parent is always greater than or equal to
% that of a child. This is discussed in more detail in World Space Error Metrics and Bounding Balls
% sections of this file. Also, it is discussed in detail in Section A. Figure 3 shows an example of
% what is meant by a T-junction.
%
% Also notice that the corner vertices aren't included in the tree (A, E, U, and V) because these
% vertices must always be active to prevent holes in the mesh.

% Build the adjacency matrix for the DAG
function DAG = addchildren(DAG, node, level)
  sz = numel(DAG)^0.25;
  % for 17x17 max level of tree is 8, for 9x9 its 6, for 5x5 its 4, etc...
  maxLevel = log2(sz-1)*2;
  if level < maxLevel
    % level 1 is first level of the DAG with root node
    maxDist = (sz-1)/2;
    % determine if children are diagonal
    diag = -mod(level,2)+1; % == (mod(level,2)==0)
    % determine distance to travel to children, for 17x17 follows pattern 8 4 4 2 2 1 1
    dist = maxDist/(2^((level-mod(level,2))/2));
    
    % compute potential locations of children
    if diag==1
      c1 = node+[dist,dist];
      c2 = node+[-dist,dist];
      c3 = node+[dist,-dist];
      c4 = node+[-dist,-dist];
    else
      c1 = node+[dist,0];
      c2 = node+[-dist,0];
      c3 = node+[0,dist];         
      c4 = node+[0,-dist];
    end
    
    % add children to graph (some children are off the grid so are invalid)
    if validPos(c1,sz)
      DAG(getidx(node,sz), getidx(c1,sz)) = 1;
      DAG = addchildren(DAG, c1, level+1);  
    end
    if validPos(c2,sz)
      DAG(getidx(node,sz), getidx(c2,sz)) = 1;
      DAG = addchildren(DAG, c2, level+1);  
    end
    if validPos(c3,sz)
      DAG(getidx(node,sz), getidx(c3,sz)) = 1;
      DAG = addchildren(DAG, c3, level+1);  
    end
    if validPos(c4,sz)
      DAG(getidx(node,sz), getidx(c4,sz)) = 1;
      DAG = addchildren(DAG, c4, level+1);  
    end
  end
end

% get the child positions of the given node in the DAG (return positions in a matrix of row vectors)
function children = getChildren(DAG, node)
  sz = numel(DAG)^0.25;
  nodeIdx = getidx(node,sz);
  childrenIdx=find(DAG(nodeIdx,:)>0);
  children=zeros(numel(childrenIdx),2);
  for i=1:numel(childrenIdx)
    children(i,:)=getpos(childrenIdx(i),sz);
  end
end

% generate unique index for x,y values in sz x sz grid
function idx = getidx(pos, sz)
  idx = pos(1)+pos(2)*sz;
end

% retrieve unique x,y position from index in sz x sz grid
function pos = getpos(idx, sz)
  pos = [0,0];
  pos(1) = mod(idx,sz);
  pos(2) = (idx-pos(1))/sz;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                         Active Vertices and Screen Space error
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Compute the isotropic screen space error using Equation 8
function p = computePIsotropic(e, r, cam, z)
  % A FEW ASSUMPTIONS ABOUT SCREEN SIZE AND ASPECT RATIO
  w = 640;          % Pixels across screen
  phi = 60*pi/180;  % FOV (azimuth)
  lambda = w/phi;
  
  sz = size(e);
  for xIdx=1:sz(1)
    for yIdx=1:sz(2)
      camDist = norm([xIdx-1 yIdx-1 z(xIdx,yIdx)]-cam);
      % if camera is within B sphere then vertex MUST be active (see paragraph above equation 7)
      if camDist < r(xIdx, yIdx)
        % Infinite error, forces vertex to be active
        p(xIdx, yIdx) = Inf;
      else
        % Equation 7
        p(xIdx, yIdx) = lambda * e(xIdx, yIdx) / (camDist-r(xIdx, yIdx));
      end
    end
  end
end

% Return a binary matrix indicating which vertices are active. based on Equation 8 or 11
function v = getActiveVerts(p, tau, v)
  v(p>tau)=1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                                 Utility functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% rotate a vector by angle assumes row vector for vec
function rotatedVec = rotateVec(vec,deg)
  M = [cosd(deg) sind(deg); ...
      -sind(deg) cosd(deg)];
  rotatedVec = round(vec*M);
end

% check if pos is in valid range ([0,sz-1])
function v = validPos(pos,sz)
  v = (sum(pos>=0 & pos<=(sz-1))==2);
end

% generate a sinc function for sample dataset in a regular sz x sz grid (sz=2^n+1)
function z = gensinc(sz)
  [x,y] = meshgrid(0:sz-1,0:sz-1);
  r = sqrt((x-(sz-1)/2).^2+(y-(sz-1)/2).^2);
  z = sin(r*16/(sz-1))./(r*16/(sz-1));
  z((sz+1)/2,(sz+1)/2) = 1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%           Functions used for creating triangle strip from active vertices
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function V=meshrefine(verts)
  V = [0,0; ...
       0,0];
  parity=0;
  sz = size(verts);
  sz = sz(1)-1;
  n = log2(sz)*2;
  points=[sz/2 0 ; sz 0;  ...
          sz sz/2; sz sz; ...
          sz/2 sz; 0  sz;  ...
          0  sz/2; 0  0];
  for row=1:2:8
    j=points(row,:);
    k=points(row+1,:);
    [V,parity]=submeshrefine(V,[sz/2,sz/2],j,n,parity,verts);
    [V,parity]=tstripappend(V,k,1,parity,2);
  end
  
  % remove first vertex in V
  Vsz=size(V);
  V=V(2:Vsz(1),:);
end

function [V,parity]=submeshrefine(Vin,i,j,l,parity,verts)
  V=Vin;

  if l>0 && verts(i(1)+1,i(2)+1)==1
    childLeft = cl(i,j);
    childRight = cr(i,j);
    [V,parity]=submeshrefine(V,j,childLeft,l-1,parity,verts);
    [V,parity]=tstripappend(V,i,mod(l,2),parity,verts);
    [V,parity]=submeshrefine(V,j,childRight,l-1,parity,verts);
  end
end

function [V,parity] = tstripappend(Vin,vert,p,parity)
  V=Vin;
  vsz=size(V); n=vsz(1);
  if (sum(abs(vert-V(n-1,:)))~=0) && (sum(abs(vert-V(n,:)))~=0)
    if p~=parity
      parity=p;
    else
      V = [V;V(n-1,:)];
    end
    V = [V;vert];
  end
end

% Determine the left child of the triangle defined by vi/vj assumes j is a child of i
function c = cl(vi, vj);
  xi = vi(1);
  yi = vi(2);
  xj = vj(1);
  yj = vj(2);
  
  xd = xj-xi;
  yd = yj-yi;
  mdist=max([abs(xd),abs(yd)]);
  
  % how far to move to the next child
  if abs(xd)==abs(yd)
    cdist=mdist;
    diag=0;
  else
    cdist=mdist/2;
    diag=1;
  end
  
  % narrow down child to two candidates
  if diag==1
    if xd==0
      xc1=xi-cdist;
      xc2=xi+cdist;
      yc1=(yi+yj)/2;
      yc2=yc1;
    else % yd==0
      yc1=yi-cdist;
      yc2=yi+cdist;
      xc1=(xi+xj)/2;
      xc2=xc1;
    end
    
    % determine which one is left
    cross1=cross([xi-xj,yi-yj,0],[xc1-xj,yc1-yj,0]);
    if (cross1(3)>0)
      xc=xc1;
      yc=yc1;
    else
      xc=xc2;
      yc=yc2;
    end
  else % diag==0
    xc1=xj;
    yc1=yj-yd;
    xc2=xj-xd;
    yc2=yj;
    
    cross1=cross([xi-xj,yi-yj,0],[xc1-xj,yc1-yj,0]);
    if (cross1(3)>0)
      xc=xc2;
      yc=yc2;
    else
      xc=xc1;
      yc=yc1;
    end
  end
  
  c=[xc yc];
end

% Determine the right child of the triangle defined by vi/vj assumes j is a child of i
function c = cr(vi, vj);
  xi = vi(1);
  yi = vi(2);
  xj = vj(1);
  yj = vj(2);
  
  xd = xj-xi;
  yd = yj-yi;
  mdist=max([abs(xd),abs(yd)]);
  
  % how far to move to the next child
  if abs(xd)==abs(yd)
    cdist=mdist;
    diag=0;
  else
    cdist=mdist/2;
    diag=1;
% Build the adjacency matrix for the DAG
function DAG = addchildren(DAG, node, level)
  sz = numel(DAG)^0.25;
  % for 17x17 max level of tree is 8, for 9x9 its 6, for 5x5 its 4, etc...
  maxLevel = log2(sz-1)*2;
  if level < maxLevel
    % level 1 is first level of the DAG with root node
    maxDist = (sz-1)/2;
    % determine if children are diagonal
    diag = -mod(level,2)+1; % == (mod(level,2)==0)
    % determine distance to travel to children, for 17x17 follows pattern 8 4 4 2 2 1 1
    dist = maxDist/(2^((level-mod(level,2))/2));
    
    % compute potential locations of children
    if diag==1
      c1 = node+[dist,dist];
      c2 = node+[-dist,dist];
      c3 = node+[dist,-dist];
      c4 = node+[-dist,-dist];
    else
      c1 = node+[dist,0];
      c2 = node+[-dist,0];
      c3 = node+[0,dist];
      c4 = node+[0,-dist];
    end
    
    % add children to graph (some children are off the grid so are invalid)
    if validPos(c1,sz)
      DAG(getidx(node,sz), getidx(c1,sz)) = 1;
      DAG = addchildren(DAG, c1, level+1);  
    end
    if validPos(c2,sz)
      DAG(getidx(node,sz), getidx(c2,sz)) = 1;
      DAG = addchildren(DAG, c2, level+1);  
    end
    if validPos(c3,sz)
      DAG(getidx(node,sz), getidx(c3,sz)) = 1;
      DAG = addchildren(DAG, c3, level+1);  
    end
    if validPos(c4,sz)
      DAG(getidx(node,sz), getidx(c4,sz)) = 1;
      DAG = addchildren(DAG, c4, level+1);  
    end
  end
end

  end
  
  % narrow down child to two candidates
  if diag==1
    if xd==0
      xc1=xi-cdist;
      xc2=xi+cdist;
      yc1=(yi+yj)/2;
      yc2=yc1;
    else % yd==0
      yc1=yi-cdist;
      yc2=yi+cdist;
      xc1=(xi+xj)/2;
      xc2=xc1;
    end
    
    % determine which one is left
    cross1=cross([xi-xj,yi-yj,0],[xc1-xj,yc1-yj,0]);
    if (cross1(3)<0)
      xc=xc1;
      yc=yc1;
    else
      xc=xc2;
      yc=yc2;
    end
  else % diag==0
    xc1=xj;
    yc1=yj-yd;
    xc2=xj-xd;
    yc2=yj;
    
    cross1=cross([xi-xj,yi-yj,0],[xc1-xj,yc1-yj,0]);
    if (cross1(3)<0)
      xc=xc2;
      yc=yc2;
    else
      xc=xc1;
      yc=yc1;
    end
  end
  
  c = [xc yc];
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                             Plotting functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Plot the vertices in a top down (xy) view.
function plotVerts(verts)
  hold on;
  sz=size(verts);
  colors='brg';
  for x=1:sz(1)
    for y=1:sz(2)
      if verts(x,y)>0
        plot(x-1,y-1,' o', 'LineWidth', 2, 'Color', colors(verts(x,y)));
      end
    end
  end
  
  axis([-0.25 sz(1)-0.75 -0.25 sz(2)-0.75]);
  grid on;
  set(gca, 'xtick', [0:1:sz(1)-1]);
  set(gca, 'ytick', [0:1:sz(2)-1]);
end

% Plot the 3d triangle strip. lstrip should be an Nx2 matrix where N is the number of vertices
% in triangle strip. First column are X values and second are Y values.
function plotTStrip(lstrip,z)
  sz=size(lstrip);
  plot3([lstrip(1,1) lstrip(2,1)], ...
        [lstrip(1,2) lstrip(2,2)], ...
        [z(lstrip(1,1)+1, lstrip(1,2)+1) z(lstrip(2,1)+1, lstrip(2,2)+1)],'b', 'LineWidth', 2);
  hold on;
  for r=3:sz(1)
    if sum(lstrip(r,:)==lstrip(r-1,:))~=0 || ...
       sum(lstrip(r,:)==lstrip(r-2,:))~=0 || ...
       sum(lstrip(r-2,:)==lstrip(r-1,:))~=0
      plot3([lstrip(r,1) lstrip(r-1,1)], ...
            [lstrip(r,2) lstrip(r-1,2)], ...
            [z(lstrip(r,1)+1, lstrip(r,2)+1) z(lstrip(r-1,1)+1, lstrip(r-1,2)+1)],'b', 'LineWidth', 2);
      plot3([lstrip(r,1) lstrip(r-2,1)], ...
            [lstrip(r,2) lstrip(r-2,2)], ...
            [z(lstrip(r,1)+1, lstrip(r,2)+1) z(lstrip(r-2,1)+1, lstrip(r-2,2)+1)],'b', 'LineWidth', 2);      
    end
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%                      Unused functions for testing
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Plot the DAG, not very useful but ensures that things are what they seem (VERY VERY SLOW)
function plotDag(DAG, node, level)
  colors = ...
    [0 0 1; ... % blue
     0 1 0; ... % green
     1 0 0; ... % red
     0 1 1; ... % cyan
     1 0 1; ... % purple
     1 1 0; ... % yellow
     0 0 0];    % black

  sz = numel(DAG)^0.25;
     
  idx = getidx(node,sz);
  idxC = find(DAG(idx,:)>0); % find all children
  
  % iterate through children and draw line from parent to child
  for c = 1:numel(idxC)
    nodeC = getpos(idxC(c),sz);
  
    plot([node(1) nodeC(1)],[node(2) nodeC(2)],'LineWidth',2,'Color',colors(mod(level-1,7)+1,:));
    hold on;
    plotDag(DAG, nodeC, level+1);
  end
end

% test to make sure eprev is always greater than e(node)
function teste(DAG, node, e, eprev)
  if e(node(1)+1, node(2)+1) > eprev
    fprintf('Error at Vertex(%i, %i)\n', node(1), node(2));
  end
  cpos = getChildren(DAG, node);
  for i=1:numel(cpos)/2
    cnode = cpos(i,:);
    teste(DAG, cnode, e, e(node(1)+1, node(2)+1));
  end
end