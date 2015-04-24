%for i=1:10

d = 'plots/';

files = dir(strcat(d,'plot*.txt'));
for file = files'

%load(strcat(d,file.name));

%fileID = fopen(sprintf('%s%d%s', 'plot', i,'.txt'),'r');
fileID = fopen(strcat(d,file.name));
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
saveas(figh,strcat('plots/',out),'jpg');
end
