%   File : testRender.m
% Author : Josh Gleason
%   Date : 05/16/14
% This script is meant to perform simple mesh render based on a small artificial sinc function
% dataset. Tests the error computation presented in "Lindstrom et al. Terrain simplification
% Simplified (2002)" in Sections B and C. And renders a triangle mesh using the method
% described in Section D. This script favors readability over speed but does offload pre
% processed data to the hard disk to reduce run time after it has been computed the first time.

% Program Entry
% Output
%   p      : screen space error
%   z      : height map of sinc function
%   tstrip : Vertives of triangle strip
% Input (optional)
%   sz     : Number of rows/columns in height map
%   tau    : Screen space error threshold (pixels)
%   camPos : 1x3 row vector of camera position (x,y,z)
function [p, z, tstrip]=testRender(sz, tau, camPos, makeVideo)
  % Query user for input parameters
  if nargin < 4
    [sz, tau, camPos, makeVideo] = getUserInput();
  else
    sz = 2^ceil(log2(sz-1))+1;
  end

  % Try to load preprocessed data from fname
  [valid, z, e, r] = initValues(sz);

  % Preprocess data if necessary. Save off core so it doesn't need to be done again
  if ~valid
    % Perform preprocessing on data (This can take a very long time!)
    [e, r] = preProcess(sz, z);
    % Save preprocessed data using MATLAB .mat format
    save(sprintf('PreProcessed%g.mat', log2(sz-1)),'e','r','z');
  end

  % Build a single plot or a video depending on user input
  if makeVideo
    [p,tstrip] = buildVideo(sz, z, e, r, camPos);
  else
    [p,v,tstrip] = computeMesh(sz, tau, camPos, z, e, r);
    plotAll(sz, z, v, tstrip, camPos);
  end
end

% Build a 30 Hz video moving around the scene
function [p, tstrip] = buildVideo(sz, z, e, r, camPos)
  if exist('OCTAVE_VERSION', 'builtin')
    fprintf('Octave does not have the ability to create videos, please use MATLAB\n');
    p=[]; tstrip=[];
    return;
  end
  
  % Get user input for video file name
  fname = uiputfile({'*.mp4', 'MPEG-4 Video File'});
  assert(~isempty(fname) && ~exist(fname,'dir'), 'Filename must be valid');
  
  writer = VideoWriter(fname,'MPEG-4');
  writer.Quality = 80;
  writer.FrameRate = 30;
  open(writer);
  
  % Initialize path for camera
  path = initPath(4:1/30:5, sz, camPos);

  for i=1:numel(path)/3
    % Compute the screen space error and triangle strip
    [p, v, tstrip] = computeMesh(sz, tau, camPos, z, e, r);
    % Plot figure
    [imgMesh, imgVerts] = plotAll(sz, z, v, tstrip, camPos); 
    close(1); close(2);
    %fprintf('Average p value : %g\n',mean(p(~isinf(p))));
    fprintf('Percentage Complete %g%%\n',i/(numel(path)/3)*100);
    % Adjust camera position
    camPos = path(i,:);
    imgFinal = [imgMesh imgVerts];
    
    % Add image to file
    writer.writeVideo(imgFinal);
  end
  close(writer);
end

function path = initPath(t, sz, camPos)
  path = zeros(numel(t),3);
  % adjust distance based on sine wave while at the same time rotating in
  % azimute at a constant speed while varying rotation in elevation in a
  % sine wave
  % Need to scale not translate to move single point from origin
  count = 1;
  
  % Translate so center of plot is centered
  dx = (sz-1)/2; dy = (sz-1)/2; dz = (sz-1)/2;
  T1 = [1 0 0 -dx; ...
        0 1 0 -dy; ...
        0 0 1 -dz; ...
        0 0 0 1];
  T6 = [1 0 0 dx; ...
        0 1 0 dy; ...
        0 0 1 dz; ...
        0 0 0 1];
  for dt=t
    % Rotate around X and Y using sin wave motion
    theta = pi/4*sin(pi/7*dt);
    T2 = [1 0           0          0; ...
          0 cos(theta) -sin(theta) 0; ...
          0 sin(theta)  cos(theta) 0; ...
          0 0           0          1];
    T3 = [cos(theta) 0 sin(theta) 0; ...
          0          1 0          0; ...
         -sin(theta) 0 cos(theta) 0; ...
          0          0 0          1];
    
    % Rotate around z linearly
    theta = pi/5*dt;
    T4 = [cos(theta) -sin(theta) 0 0; ...
          sin(theta)  cos(theta) 0 0; ...
          0           0          1 0; ...
          0           0          0 1];
    
    % Scale by sine function in X and Y
    T5 = [(sin(pi/3*dt)+2)*0.5 0 0 0; ...
          0 (sin(pi/3*dt)+2)*0.5 0 0; ...
          0 0 1 0; ...
          0 0 0 1];
   
    pos4 = T6*T5*T4*T3*T2*T1*[camPos 1]';
    pos4(1:3) = pos4(1:3)/pos4(4);
    path(count,:) = pos4(1:3)';

    count = count+1;
  end
  %plot3(path(:,1),path(:,2),path(:,3))
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                   I/O Operators
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Query user for size (sz), screen space error threshold (tau) and camera
% position (camPos)
function [sz, tau, camPos, makeVideo] = getUserInput()
  % get size of array (number of rows and columns) round up to nearest 2^n+1
  sz = 2^4+1;
  n = input(sprintf('Enter size of array (will be scaled to nearest 2^n+1) (Default %6g) : ', sz));
  if ~isempty(n)
    powr = ceil(log2(n-1));
    sz=2^powr+1;
  end

  % pixel error threshold based on 60 degree FOV and 640 pixel screen resolution
  tau = 1;
  tauVal=input(sprintf('Pixel Error (tau) (Default %g) : ', tau));
  if ~isempty(tauVal), tau = tauVal; end
  
  % set a camera position. If the camera is close the mesh will be dense.
  camPos = [-6 -25 2];
  camX = input(sprintf('Camera X (Default %6g) :', camPos(1)));
  if ~isempty(camX), camPos(1) = camX; end
  camY = input(sprintf('Camera Y (Default %6g) :', camPos(2)));
  if ~isempty(camY), camPos(2) = camY; end
  camZ = input(sprintf('Camera Z (Default %6g) :', camPos(3)));
  if ~isempty(camZ), camPos(3) = camZ; end
  
  % Ask if user wants to build a video
  makeVideo = input('Do you want to build a Video? (1/0 Default 0) : ');
  if isempty(makeVideo) || makeVideo~=1, makeVideo=0; end
end

% Attempt to load preprocessed data from a file
function [valid, z, e, r] = initValues(sz)
  valid = 1;
  try
    powr = log2(sz-1);
    fname = sprintf('PreProcessed%g.mat',powr);
    S = load(fname);
    e = S.e; r = S.r; z = S.z;
  catch
    fprintf('Unable to load PreProcessed Data\n');
    valid = 0;
    z = gensinc(sz);
    e = []; r = [];
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                        Mesh simplification step (every frame)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Compute nested screen space error and triangle mesh
% Input Parameters
%   sz     : The number of rows/columns in the height map (2^n+1)
%   tau    : Maximum screen space error allowed (in pixels)
%   camPos : A 1x3 row vector representing the camera position
%   z      : The height map (z values)
%   e      : Nested screen space error (see preProcess function)
%   r      : Nested bounding sphere radii (see preProcess function)
% Output Parameters
%   p      : Nested screen space error
%   tstrip : The triangle mesh as a continuous triangle strip (indexed)
function [p, v, tstrip] = computeMesh(sz, tau, camPos, z, e, r)
    % initialize active vertices (corners and center are active by default)
    v = zeros(sz,sz);
    v([1 sz],[1 sz])=1; v((sz+1)/2,(sz+1)/2)=1;
    
    % Compute screen space error using isotropic projection (simpler than perspective)
    % using Equation 7 (Optionally I could be using perspective screen space error described
    % in Equation 10). It should be noted that this value doesn't need to be computed for
    % every node, if a parent node is deactivated (p <= tau) then I know because of the
    % monatonic property of this metric, that all the children will also be deactivated.
    p = computePIsotropic(e, r, camPos, z);
    
    % Filter vertices with screen space error above pixel threshold (tau). The smaller tau is
    % the more vertices activated based ocomputeEMaxn Equation 8 or 11.
    v = getActiveVerts(p, tau, v);
    
    % Compute the triangle strip vertices using the method described in Section D.
    tstrip = meshrefine(v);
    
    % TODO: Perform View Frustum Culling (Section E)
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                           Data preprocessing step
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Compute the two off-core metrics used for computing the screen space error metric.
% Input Parameters
%   sz: The number of rows/columns in the height map (2^n+1)
%   z:  The height map (z values)
% Output
%   e : World space error metric (nested)
%   r : Bounding ball diameter
function [e, r] = preProcess(sz, z)
  % Initialize all the variables that are needed for this calculation.
    % raw world space error
    einc = zeros(sz,sz);
    emax = zeros(sz,sz);
    % monatonically increasing error (in terms of DAG traversal)
    e = zeros(sz,sz);
    % radius of bounding ball used in screen space error calculation
    r = zeros(sz,sz);
    % This is the root nodes position
    root = [(sz-1)/2,(sz-1)/2];
    % this will be the Directed Acyclic graph's adjacency matrix. Using a sparse matrix
    DAG = spalloc(sz*sz, sz*sz, 4*sz*(sz-1));

  % Preprocessing on dataset
    % These values would be stored as metadata in the file containing the heightmap.

    % I need to build the DAG of the scene. The center of the mesh is the parent. Based on
    % Section A in the paper. See Figure 2 and DAG section of source code for help
    % understanding the graph topology.
    DAG = addchildren(DAG, root, 1);
    % compute radius of bounding balls using Equation 3.
    r = boundingBall(DAG, root, z, 1, r);
    % compute actual world space error using Equation 4 and 5
    einc = computeEInc(DAG, z, root, 1, einc);
    emax = computeEMax(DAG, z, einc, root, 1, emax);
    % compute monatonically increasing world space error (in terms that e_ancestor <= e_node)
    % using Equation 2.
    e = computeE(DAG, emax, root, 1, e);
    
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                           Directed Acyclic Graph (DAG)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

% get the parents of a given child node in the DAG (return positions in a matrix of row vectors)
function parents = getParents(DAG, node)
  sz = numel(DAG)^0.25;
  nodeIdx = getidx(node,sz);
  parentsIdx = find(DAG(:,nodeIdx)>0);
  parents = zeros(numel(parentsIdx),2);
  for i=1:numel(parentsIdx)
    parents(i,:) = getpos(parentsIdx(i),sz);
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               Compute Bounding Balls (Lateral World Space Error)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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
function r=boundingBall(DAG, node, z, level, r)
  sz = numel(DAG)^0.25;
  maxLevel = log2(sz-1)*2;
  if level == maxLevel % leaf
    r(node(1)+1, node(2)+1) = 0;
  else
    cpos = getChildren(DAG, node);
    for i=1:numel(cpos)/2
      cnode = cpos(i,:);
      if r(cnode(1)+1, cnode(2)+1) == 0
        r=boundingBall(DAG, cnode, z, level+1, r);
      end
              
      % recurse down the tree to determine value of r. This recursion visits
      % the lowest nodes first. Everything below should already have a validPos
      % value for r. The bbRadius does not modify r it simply returns the value
      % of r(node). Make sure the z value is included in this calculation
      r(node(1)+1, node(2)+1) = bbRadius(DAG, node, cnode, z, level+1, r, 0);
      
    end
  end
end

% find euclidean length of vector
function l = euclidLen(node)
    l = sqrt(sum(node.*node,numel(size(node))));
end

% Used to compute the "otherwise" part of Equation 3. Used by boundingBall function
function maxval=bbRadius(DAG, inode, node, z, level, r, maxval)
  sz = numel(DAG)^0.25;
  maxLevel = log2(sz-1)*2;
  nodez = [node z(node(1)+1, node(2)+1)];
  % last level must be included
  if level <= maxLevel
    % compute the distance from inode to node (Equation 3 in paper)
    inodez = [inode z(inode(1)+1, inode(2)+1)];
    dist = euclidLen(nodez-inodez) + r(node(1)+1, node(2)+1);
    maxval = max([dist maxval]);
    cpos = getChildren(DAG, node);
    for i=1:numel(cpos)/2
      cnode = cpos(i,:);
      maxval = bbRadius(DAG, inode, cnode, z, level+1, r, maxval);
    end
  end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                        World Space Height Error Metrics
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% World space z-error measures the amount of elevation (z-axis) error introduced by NOT
% activating a vertex. i.e. This answers the question. If you were to remove this vertex
% from the mesh, how much elevation error would be introduced in world space? This is
% described in more detail below and in Sections C.1 and B.
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
% edge for that matter). This means we'll want to use linear interpolation or
% homogenous coordinatates to determine the z value at any point inside the triangle.
% I decided on linear interpolation for no particular reason.
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
  sz = numel(DAG)^0.25;
  maxLevel = log2(sz-1)*2;
  if maxLevel == level % leaf
    % bottom level
    emax(node(1)+1, node(2)+1) = einc(node(1)+1, node(2)+1);  
  else
    cpos = getChildren(DAG, node);
    
    % call recursive maximum function on children
    for i=1:(numel(cpos)/2)
      cnode = cpos(i,:);
      if emax(cnode(1)+1, cnode(2)+1) == 0
        % I now have a child node that has yet to be set. I need to find both
        % both triangles it intersects and test them seperately. This can be
        % done by finding all the parents of the node (column in DAG)
        ppos = getParents(DAG, cnode);
        
        emax(cnode(1)+1, cnode(2)+1) = einc(cnode(1)+1, cnode(2)+1);
        % Now I can define the triangle or triangles to bisection search
        for j=1:(numel(ppos)/2)
          pnode = ppos(j,:);
          
          % triangle defined by pnode->cnode. Okay find the left and right nodes
          vec = cnode-pnode;
          vec090 = rotateVec(vec,90);
          vec270 = rotateVec(vec,270);
          lnode = cnode + vec090;
          rnode = cnode + vec270;
          
          emax(cnode(1)+1, cnode(2)+1) = ...
            findMaxError(DAG, z, ...
              pnode, cnode, ...                       % bisecting line of current triangle
              pnode, lnode, rnode, ...                % triangle t
              level+1, emax(cnode(1)+1, cnode(2)+1)); % level and current max
        end
        
        % perform the same recusive search recursively on all nodes in the graph
        emax = computeEMax(DAG, z, einc, cnode, level+1, emax);
      end
    end
  end
end

% Find the maximum error by recursively searching down the left and right children of the
% of the triangle defined by pnode->node and compare with the error of the triangle defined
% by the 3 positions of mnode, lnode, rnode
function maxError = findMaxError(DAG, z, pnode, node, mnode, lnode, rnode, level, curError)
  sz = numel(DAG)^0.25;
  maxLevel = log2(sz-1)*2;
  if level < maxLevel
    leftChild = cl(pnode, node);
    rightChild = cr(pnode, node);
    
    % find z of triangle mnode, lnode, and rnode at position leftChild and rightChild
    zFakeLeft  = getTriZ(z, mnode, lnode, rnode, leftChild);
    zFakeRight = getTriZ(z, mnode, lnode, rnode, rightChild);
    zRealLeft  = z(leftChild(1)+1, leftChild(2)+1);
    zRealRight = z(rightChild(1)+1, rightChild(2)+1);
    
    maxError = max([curError abs(zFakeLeft-zRealLeft) abs(zFakeRight-zRealRight)]);
    
    % call this recursively on left and right children
    maxError = findMaxError(DAG, z, node, leftChild, mnode, lnode, rnode, level+1, maxError);
    maxError = findMaxError(DAG, z, node, rightChild, mnode, lnode, rnode, level+1, maxError);
  else
    maxError = curError;
  end
end

% Find the Z value by linear interpolation across triangle a,b,c at pos
function zVal = getTriZ(z, a, b, c, pos)
  xA = a(1);
  xB = b(1);
  xC = c(1);

  yA = a(2);
  yB = b(2);
  yC = c(2);  
  
  zA = z(a(1)+1, a(2)+1);
  zB = z(b(1)+1, b(2)+1);
  zC = z(c(1)+1, c(2)+1);
  
  constA = yA*(zB-zC) + yB*(zC-zA) + yC*(zA-zB);
  constB = zA*(xB-xC) + zB*(xC-xA) + zC*(xA-xB);
  constC = xA*(yB-yC) + xB*(yC-yA) + xC*(yA-yB);
  constD = -constA*xA - constB*yA - constC*zA;
  
  zVal = -(constA/constC)*pos(1) - (constB/constC)*pos(2) - constD/constC;
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
    maxval = ehat(node(1)+1, node(2)+1);
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                  Active Vertices and Screen Space Error Metrics
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% The screen space error metric is the final metric used to determine if a vertex
% will be activated or not. This metric for each vertex using the camera position, the
% vertices bounding ball, and the vertices world space error metric. It is also based
% on the FOV per pixel which should be constant. The screen space error is,
% computed every frame. Described in detail in Sections B, C.2 and C.3.

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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           Functions used for creating triangle strip from active vertices
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% TODO: Get a better understanding of these functions, enough to describe them in detail.
%
% The meshrefine function takes a valid set of active vertices and generates the list
% of vertices for rendering the final mesh as a single triangle strip.

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
    [V,parity]=tstripappend(V,k,1,parity);
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
    [V,parity]=tstripappend(V,i,mod(l,2),parity);
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                 Utility functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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
  z = sin(r*16/(sz-1)*2)./(r*16/(sz-1)*2);
  z(isnan(z)) = 1;
  z = z*(sz-1);
end

% given a row/column in a matrix get linear index for it  
function idx=getRowColIdx(row, col, sz)
  idx = (col-1)*sz+(row-1)+1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                             Plotting functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


function img = captureFigure(f)
  if exist('OCTAVE_VERSION', 'builtin')
    img = [];
  else % MATLAB
    data = getframe(f);
    img = data.cdata;
  end
end

% Plots the final output to the user
function [imgMesh, imgVerts] = plotAll(sz, z, v, tstrip, camPos)
  monPos = get(0,'MonitorPositions');
  maxX = abs(monPos(3)-monPos(1));
  maxY = abs(monPos(4)-monPos(2));
  imsz = [640 480];
  
  % Plot active vertices
  f=figure(1); hold off;
  plotVerts(v);
  set(f, 'Color', [1 1 1]);
  figPos = get(f, 'Position');
  set(f, 'Position', [min(figPos(1),maxX-imsz(1)-80) min(figPos(2),maxY-imsz(2)-200) imsz(1) imsz(2)]);
  
  % Get capture of figure
  imgVerts = captureFigure(f);
  
  % Plot the triangle mesh as well as the camera position (camera is red "O")
  f=figure(2); hold off;
  plotTStrip(tstrip,z); hold on;

  % Move the camera and point it at the center of the sceen
  figPos = get(f, 'Position');
  set(f, 'Color', [1 1 1]);

  % Make axis for 3d and scale ticks to square things appear square
  axis equal;
  if ~exist("OCTAVE_VERSION", "builtin")
    plot3(camPos(1), camPos(2), camPos(3), 'ro');
    set(gca, 'CameraPosition', camPos);
    set(gca, 'CameraTarget', [(sz-1)/2 (sz-1)/2 0.5]);
    set(f, 'Position', [min(figPos(1),maxX-imsz(1)-80) min(figPos(2),maxY-imsz(2)-200) imsz(1) imsz(2)]);
    
    axis vis3d off;
    % Set perspective projection
    camproj perspective;
    % Set view angle to 60 degrees
    camva(60);
  end
  
  % Get capture of figure
  imgMesh = captureFigure(f);
end

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
  sz=size(z); sz=sz(1);
  lstripSz=size(lstrip);
  [x,y] = meshgrid(0:sz-1,0:sz-1);
  c = zeros(numel(z),3);
  
  % initialize triangle index container and color container
  tri = zeros(0,3);
  
  for r=3:lstripSz(1)
    if sum(lstrip(r,:)==lstrip(r-1,:))~=0 || ...
       sum(lstrip(r,:)==lstrip(r-2,:))~=0 || ...
       sum(lstrip(r-2,:)==lstrip(r-1,:))~=0
      p1Idx = getRowColIdx(lstrip(r,1)+1,   lstrip(r,2)+1,   sz);
      p2Idx = getRowColIdx(lstrip(r-1,1)+1, lstrip(r-1,2)+1, sz);
      p3Idx = getRowColIdx(lstrip(r-2,1)+1, lstrip(r-2,2)+1, sz);
      
      % Add to triangle list
      tri = [tri; p1Idx p2Idx p3Idx];
    end
  end
  %trimesh(tri,x(:), y(:), z(:),'EdgeColor','b');
  trimesh(tri,x(:), y(:), z(:),'EdgeColor','none','FaceColor','interp');
end
