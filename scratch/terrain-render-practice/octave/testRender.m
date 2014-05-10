%   File : testRender.m
% Author : Josh Gleason
%   Date : 05/09/14
% This script is meant to perform simple mesh render based on a small artificial sinc function
% dataset. Tests the error computation presented in "Lindstrom et al. Terrain
% implification Simplified (2002)" in Section C. And renders a triangle mesh using the
% method described in Section D. This script favors readability over speed and makes
% no attempts to optimize calculations.

function [p, z, e, r]=testRender()
  sz = 2^5+1;
  % generate a sinc function for sample dataset in a regular 17 x 17 grid
  z = gensinc(sz);
  % active vertices (corners are active by default)
  v = zeros(sz,sz);
  v(1,1) = 1; v(1,sz) = 1; v(sz,1) = 1; v(sz,sz) = 1;
  % world space error
  einc = zeros(sz,sz);
  % monatonically increasing error (in terms of DAG traversal)
  e = zeros(sz,sz);
  % screen space error
  p = zeros(sz,sz);
  % radius of bounding ball used in screen space error calculation
  r = zeros(sz,sz);
  % set a camera position (ignoring orientation of camera for this test)
  camPos = [0,-16,8];
  
  center = [(sz-1)/2,(sz-1)/2];
  
  % I need to build the DAG of the scene. The center of the mesh is the parent. I will
  % use an adjacency matrix to represent the DAG
  DAG = zeros(sz*sz,sz*sz);
  DAG = addchildren(DAG, center, 1);
  
  % % Plots the DAG (VERY VERY SLOW) just for validation
  % plotDag(DAG, [8,8], 1);
  % axis([-0.25 16.25 -0.25 16.25]);
  % set(gca, 'xtick', 0:1:16);
  % set(gca, 'ytick', 0:1:16);
  
  % compute radius of bounding balls
  r = boundingBall(DAG, center, 1, r);
  
  % compute actual world space
  einc = computeEInc(DAG, z, center, 1, einc);
  % compute monatonically increasing world space error (in terms that e_ancestor <= e_node)
  e = computeE(DAG, einc, center, 1, e);
    
  % Compute screen space error using isotropic projection (simpler than perspective)
  p = computePIsotropic(e, r, camPos, z);
  
  % % test to make sure e is monatonically increasing (sanity check)
  % teste(DAG, [8,8], e, max(max(e)));

  % Filter vertices with screen space error above pixel threshold (tau). The smaller tau is
  % the more vertices activated
  tau=0.5;
  v(p>tau)=1;
  figure(1);
  plotVerts(v);
  
  % Plot the mesh as a 3d wireframe mesh (pretty slow)
  figure(2);
  tstrip=meshrefine(v);
  plotTStrip(tstrip,z);
  hold on;
end

function p = computePIsotropic(e, r, cam, z)
  % Compute the isotropic screen space error (Equation 8)
  % A FEW ASSUMPTIONS
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

% determine result of equation 2 in the Lindstrom paper. Assumes ehat is either einc or emax
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

% determine result of equation 4 in the Lindstrom paper
function einc = computeEInc(DAG, z, node, level, einc)
  % determine we aren't on the max level
  % sz = 17 but keeping this function generic
  sz = numel(DAG)^0.25;
  % for 17x17 max level of tree is 7, for 9x9 its 5, for 5x5 its 3, etc...
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
        % find the left and right sides of the triangle
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

function rotatedVec = rotateVec(vec,deg)
  % rotate a vector by angle assumes row vector
  M = [cosd(deg) sind(deg); ...
      -sind(deg) cosd(deg)];
  rotatedVec = round(vec*M);
end

function children = getChildren(DAG, node)
  % get the child positions of the given node in the DAG
  sz = numel(DAG)^0.25;
  nodeIdx = getidx(node,sz);
  childrenIdx=find(DAG(nodeIdx,:)>0);
  children=zeros(numel(childrenIdx),2);
  for i=1:numel(childrenIdx)
    children(i,:)=getpos(childrenIdx(i),sz);
  end
end

function DAG = addchildren(DAG, node, level)
  % sz = 17 but keeping this function generic
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
  
function v = validPos(pos,sz)
  % check if position is in range of [0,16]
  v = (sum(pos>=0 & pos<=(sz-1))==2);
end

function idx = getidx(pos, sz)
  % generate unique index for x,y values in 17x17 grid
  idx = pos(1)+pos(2)*sz;
end

function pos = getpos(idx, sz)
  % retrieve unique x,y position from index in 17x17 grid
  pos = [0,0];
  pos(1) = mod(idx,sz);
  pos(2) = (idx-pos(1))/sz;
end

function z = gensinc(sz)
  % generate a sinc function for sample dataset in a regular 17x17 grid (17=2^4+1)
  [x,y] = meshgrid(0:sz-1,0:sz-1);
  r = sqrt((x-(sz-1)/2).^2+(y-(sz-1)/2).^2);
  z = sin(r*16/(sz-1))./(r*16/(sz-1));
  z((sz+1)/2,(sz+1)/2) = 1;
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

% assumes j is a child of i
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

% assumes j is a child of i
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
  
    plot([node(1) nodeC(1)],[node(2) nodeC(2)],'LineWidth',2,'Color',colors(level,:));
    hold on;
    plotDag(DAG, nodeC, level+1);
  end
end

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

