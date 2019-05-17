%% Display setting and output setup
% set(0,'ShowHiddenHandles','on'); delete(get(0,'Children')); % close windows
scr = get(groot,'ScreenSize');                              % screen resolution
phi = (1 + sqrt(5))/2;
scr_ratio = phi/3;
offset = [ scr(3)/4 scr(4)/4]; 
fig1 =  figure('Position',...                               % draw figure
        [offset(1) offset(2) scr(3)*scr_ratio scr(4)*scr_ratio]);
set(fig1,'numbertitle','off',...                            % Give figure useful title
        'name','Lab 2',...
        'Color','white');
fontName='CMU Serif';
fontSize = 22;
fontSize_Large =28;
set(0,'defaultAxesFontName', fontName);                     % Make fonts pretty
set(0,'defaultTextFontName', fontName);
set(0,'DefaultAxesColor','none');                           % Transparent background
set(groot,'FixedWidthFontName', 'ElroNet Monospace')     

% Colors
cmap = colormap(lines);

line_thin = 1.5;
line_thick = 3;
marker_size = 6;
marker_spacing = 1;
line_transparency = 0.65;

x_lim = [0 1e9];
y_lim = [0 1e3];

% Draw plots
ax1 = axes();

p1 = loglog(x,y,...
    'DisplayName','Transpose + IO (4procs)',...
    'Color',[cmap(1,:) line_transparency],...
    'MarkerFaceColor',cmap(1,:),...
	'LineStyle','-',...
	'LineWidth',line_thin,...
    'MarkerIndices',1:marker_spacing:length(x),...
    'Marker','o',...
    'MarkerSize',marker_size);
hold on


% % f_n2 = @(n) n.^2;
% f = logspace(y(8),y(end),length(y));
% vec = logspace(x(8),x(end),length(x));
% 
% p_f2 = loglog(ax1,f,...
%     'DisplayName','N^2',...
%     'Color',cmap(1,:),...
%     'MarkerFaceColor',cmap(2,:),...
% 	'LineStyle',':',...
% 	'LineWidth',line_thick);
% hold on
% 
% plotObjects = get(ax1, 'Children');
% offset =0;
% plotObjects(1).YData = plotObjects(1).YData - offset;

% Axes and labels

set(ax1,'FontSize',fontSize,...
    'Color','none',...
    'Box','off',...
    'XAxisLocation','origin',...
    'YMinorTick','on',...
    'XMinorTick','on',...
    'TickDir','both',...
    'Layer','top',...
    'LineWidth',line_thin,...
    'TickLabelInterpreter','latex');
set(ax1,...
    'Xlim',[4 ceil(max(x/1e3))*1e3],...
    'Ylim',[floor(min(min(y))/1.1) ceil(max(max(y))*1.08)]);
xticks([x']);
% xticklabels({'-3\pi','-2\pi','-\pi','0','\pi','2\pi','3\pi'})
hold on
ylabel('Time [{\mu}s] \rightarrow',...
    'FontName',fontName,...
    'FontSize',fontSize_Large);
xlabel('N [array size] \rightarrow',...
    'FontName',fontName,...
    'FontSize',fontSize_Large);

% Title and Annotations
% t1 = title(ax1,'Voltage vs Weight under different temperature conditions');

% Legend
legend1 = legend(ax1);

set(legend1,...
     'Position',[0.212355212355213 0.778979907264296 0.134169884169884 0.112828438948996],...
     'Box','off',...
     'fontSize', fontSize_Large);
hold on

% Adjust figure
ax1.Position = FillAxesPos(ax1,0.99);
% ax2.Position = ax1.Position;
% ax3.Position = ax1.Position;
hold off;

% 
% clear ax1 ax2 cmap fontName fontSize legend1 len line_thin line_thick marker_size
% clear marker_spacing offset p_hi p_lo p_nominal phi r1 r2 r3 scr scr_ratio