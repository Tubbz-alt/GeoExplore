%   File : testmesh.m
% Author : Josh Gleason
%   Date : 5/08/14
% This function realizes the triangle strip traversal algorithm presented in
% "P. Lindstrom's Terrain Simplification Simplified (2002)" and generates
% Figure 6. The code is extremely unoptimized and is here to help understand
% how the algorithm works.

function testmesh()
  verts = initVerts();
  figure(1);
  plotVerts(verts);
  title('Active Vertices');
  lstrip=meshrefine(6);
  lstripsz=size(lstrip);
  lstrip=lstrip(2:lstripsz(1),:);
  lstrip'
  %sz = size(lstrip);
  %idc = ones(1,sz(1));
  %for r=2:sz(1)
    %if sum(abs(lstrip(r,:)-lstrip(r-1,:)))==0
      %idc(r)=0;
    %end
  %end
  %lstrip=lstrip(find(idc),:);
  figure(2);
  plotVerts(verts);
  plotlstrip(lstrip);
  title('TriangleStrip');
  
end

  
  function [V,parity] = tstripappend(Vin,vert,p,parity,lvl)
    V=Vin;
    vsz=size(V); n=vsz(1);
    if (sum(abs(vert-V(n-1,:)))~=0) && (sum(abs(vert-V(n,:)))~=0)
      if p~=parity
        printspaces(lvl);
        fprintf('3:parity(V) <- %i',p);
        printspaces2(24-lvl);
        fprintf('Parity changed: %i\n',p);
        fflush(stdout);
        parity=p;
      else
        printspaces(lvl);
        fprintf('5:V <- (V, Vertex(%i,%i)) ',V(n-1,1),V(n-1,2));
        printspaces2(20-lvl);
        fprintf('Vertex Added: (%i, %i)\n',V(n-1,1),V(n-1,2));
        fflush(stdout);
        V = [V;V(n-1,:)];
      end
      printspaces(lvl);
      fprintf('6:V <- (V, Vertex(%i,%i)) ',vert(1),vert(2));
      printspaces2(20-lvl);
      fprintf('Vertex Added: (%i, %i)\n',vert(1),vert(2));
      fflush(stdout);
      V = [V;vert];
    end
  end
  
  function [V,parity]=submeshrefine(Vin,i,j,l,parity,lvl)
    V=Vin;

    verts=initVerts();
    if l>0 && verts(i(1)+1,i(2)+1)==1
      childLeft = cl(i,j);
      childRight = cr(i,j);
      printspaces(lvl);
      fprintf('2:submesh-refine(V, Vertex(%i,%i), Vertex(%i,%i), %i)\n', j(1), j(2), childLeft(1), childLeft(2), l-1);
      fflush(stdout);
      [V,parity]=submeshrefine(V,j,childLeft,l-1,parity,lvl+1);
      printspaces(lvl);
      fprintf('3:tstrip-append(V, Vertex(%i,%i), %i)\n', i(1), i(2), mod(l,2));
      fflush(stdout);
      [V,parity]=tstripappend(V,i,mod(l,2),parity,lvl+1);
      printspaces(lvl);
      fprintf('4:submesh-refine(V, Vertex(%i,%i), Vertex(%i,%i), %i)\n', j(1), j(2), childRight(1), childRight(2), l-1);
      fflush(stdout);
      [V,parity]=submeshrefine(V,j,childRight,l-1,parity,lvl+1);
    end
  end
  
  function V=meshrefine(n)
    V = [0,0; ...
         0,0];
    parity=0;
    
    points=[4 0; 8 0; 8 4; 8 8; 4 8; 0 8; 0 4; 0 0];
    for row=1:2:8
      j=points(row,:);
      k=points(row+1,:);
      printspaces(1);
      fprintf('4:submesh-refine(V, Vertex(%i,%i), Vertex(%i,%i), %i)\n', 4, 4, j(1), j(2), n);
      fflush(stdout);
      [V,parity]=submeshrefine(V,[4,4],j,n,parity,2);
      printspaces(1);
      fprintf('5:tstrip-append(V, Vertex(%i,%i), %i)\n', k(1), k(2), 1);
      fflush(stdout);
      [V,parity]=tstripappend(V,k,1,parity,2);
    end
  end

function verts=initVerts()

  verts = [1 0 1 0 1 0 0 0 1; ...
           0 0 0 1 0 0 0 0 0; ...
           0 0 1 1 1 0 1 0 0; ...
           0 0 0 1 0 0 0 0 0; ...
           1 0 1 0 1 0 0 0 1; ...
           0 0 0 0 0 0 0 0 0; ...
           0 0 1 0 0 0 0 0 0; ...
           0 0 0 0 0 0 0 0 0; ...
           1 0 0 0 1 0 0 0 1].';

  
end

function printspaces(p)
  for i=1:p
    fprintf('| ');
  end
end

function printspaces2(p)
  for i=1:p
    fprintf('  ');
  end
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

function h=plotlstrip(lstrip)
  sz=size(lstrip);
  plot([lstrip(1,1) lstrip(2,1)],[lstrip(1,2) lstrip(2,2)],'r', 'LineWidth', 2);
  count=2;
  for r=3:sz(1)
    if sum(lstrip(r,:)==lstrip(r-1,:))~=0 || ...
       sum(lstrip(r,:)==lstrip(r-2,:))~=0 || ...
       sum(lstrip(r-2,:)==lstrip(r-1,:))~=0
      plot([lstrip(r,1) lstrip(r-1,1)],[lstrip(r,2) lstrip(r-1,2)],'b', 'LineWidth', 2);
      
    end
  end
  for r=3:sz(1)
    if sum(lstrip(r,:)==lstrip(r-1,:))~=0 || ...
       sum(lstrip(r,:)==lstrip(r-2,:))~=0 || ...
       sum(lstrip(r-2,:)==lstrip(r-1,:))~=0
      plot([lstrip(r,1) lstrip(r-2,1)],[lstrip(r,2) lstrip(r-2,2)],'r', 'LineWidth', 2);
    end
  end
end
