

d = 'plots/';

files = dir(strcat(d,'plot*.txt'));
for file = files'
fullname = strcat(d,file.name);
A = load(fullname);

%fileID = fopen(fullname);
%formatSpec = '%f %f';
%sizeA = [2 Inf];
%A = fscanf(fileID,formatSpec,sizeA);
%fclose(fileID);

%A = A';

X = A(:,1);
Y = A(:,2);

figh = figure('Name',file.name);
set(figh,'visible','off');
plot(X,Y,'.');
axis equal;
%axis([-inf inf 0 inf]);
out = file.name(1:length(file.name)-4);
%saveas(figh,strcat('matlab/',out),'jpg');
print(figh,strcat('matlab/',out),'-djpg');

end

%printf("Done!\n");
