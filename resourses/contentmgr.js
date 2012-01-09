var ContentTab = Class.extend({
	Ctor: function(panel) 
	{
		this._panel = panel;
		this._element = $("<div></div>").appendTo(panel);
	},
	Select: function() {},
	Leave: function() { return true; }
});

var ContentManager = Class.extend({
	Ctor: function(tabsDiv, views, currentView) {
		this._controllers = {};
		this._currentController = null;
		this._tabsDiv = tabsDiv;
		this._tabsDiv.tabs({  select: this._ChangeContent.Bind(this) });
		
		// Create tabs contents
		this._CreateViews(views);
		
		// Select current tab
		if(currentView) this._tabsDiv.tabs( "select" , currentView );
		
		this._ControllersizeAdjuster();
	},
	
	_CreateViews: function(views) {
		for(var i =0; i < views.length; i++)
			$("#"+ views[i].Name).html(views[i].Content);
	},
	
	_ChangeContent: function(event, ui) {
		if(this._currentController && this._currentController.Leave() != true) {
			return false;
		}
		
		var tabHash = ui.tab.hash;
		// Select tab
		var tab = this._controllers[tabHash];
		if(!tab) {
			tab = this._CreateTabHandler(ui.tab.hash, ui.panel);
			if(!tab) {
				// TODO: Set tab content
				alert(ui.tab.hash + " doesn't support");
				return false;
			}
			this._controllers[tabHash] = tab;
		}
		
		this._currentController = tab;
		this._currentController.Select();
		SetCookie('FUGU_CONTENT', ui.panel.id);
		window.history.replaceState('Object', 'fugu', '/?view='+ui.panel.id);
	},
	
	_ControllersizeAdjuster: function () {
		$(window).resize(function() {
			var wh = 0;
			if ($.browser.opera && $.browser.version > "9.5") 
				wh = document.documentElement["clientHeight"];
			else 
				wh = parseInt($(window).height());

			$(".ui-tabs-panel").css("height", wh -120);
		});
		// Force resize contents
		$(window).resize();
	},
	
	_CreateTabHandler: function(tabHash, tabPanel) {
		switch(tabHash) {
			case "#viewseditor": return new ViewsEditorTab(tabPanel); break
			default: return new ContentTab(tabPanel);
		}
	}
});