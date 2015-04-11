%for i=1:10

files = dir('plot*.txt');
for file = files'

%fileID = fopen(sprintf('%s%d%s', 'plot', i,'.txt'),'r');
fileID = fopen(file.name);
formatSpec = '%f %f';
sizeA = [2 Inf];
A = fscanf(fileID,formatSpec,sizeA);
fclose(fileID);

A = A';

X = A(:,1);
Y = A(:,2);
figh = figure('Name',file.name);
set(figh,'visible','off');
plot(X,Y,'-');
%print(file.name,'-dpng');
out = file.name(1:length(file.name)-4);
saveas(figh,out,'jpg');
end
