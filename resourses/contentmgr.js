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
	Ctor: function(tabsDiv, initContent) {
		this._contents = {};
		this._currentContent = null;
		this._tabsDiv = tabsDiv;
		
		this._tabsDiv.tabs({  select: this._ChangeContent.Bind(this) });
		
		if(initContent) {
			$(initContent.Name).html(initContent.Html);
			this._tabsDiv.tabs( "select" , initContent.Name );
		}
		
		this._ContentSizeAdjuster();
	},
	
	_ChangeContent: function(event, ui) {
		if(this._currentContent && this._currentContent.Leave() != true) {
			return false;
		}
		
		var tabHash = ui.tab.hash;
		// Select tab
		var tab = this._contents[tabHash];
		if(!tab) {
			tab = this._CreateTab(ui.tab.hash, ui.panel);
			if(!tab) {
				// TODO: Set tab content
				alert(ui.tab.hash + " doesn't support");
				return false;
			}
			this._contents[tabHash] = tab;
		}
		
		this._currentContent = tab;
		this._currentContent.Select();
		SetCookie('FUGU_CONTENT', ui.panel.id); 
	},
	
	_ContentSizeAdjuster: function () {
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
	
	_CreateTab: function(tabHash, tabPanel) {
		switch(tabHash) {
			case "#viewseditor": return new ViewsEditorTab(tabPanel); break
			default: return new ContentTab(tabPanel);
		}
	}
});