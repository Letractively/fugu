dojo.require("dijit.MenuBar");
dojo.require("dijit.Menu");
dojo.require("dijit.MenuItem");
dojo.require("dijit.layout.AccordionContainer");
dojo.require("dijit.layout.ContentPane");

dojo.declare("MenuView", [dijit.layout.AccordionContainer], {
  
	_accordionLayout: null,
	
	constructor: function(args){
		dojo.safeMixin(this, args);
		this.style="border-radius:10px 10px 10px 10px;width:20%";
		this.region = "left";
		this.splitter = false;
		this.gutter = false;
		this.class = "edgePanel";
	},
	
	postCreate: function() {
		// Run any parent postCreate processes - can be done at any point
		this.inherited(arguments);
		
		var test = [{"DisplayName": "Navigation", "ID": "mcNavigation", "IconClass": "omLightbulbIcon",  "CssClass":"edgePanel"},
					{"DisplayName": "User profile", "ID": "mcUserProfile", "IconClass": "omUserIcon",  "CssClass":"edgePanel"}];

		for(var i in test){	
			var item = test[i];
			this.addChild(new dijit.layout.ContentPane({
				id: item.ID,
				title: item.DisplayName,
				iconClass: item.IconClass,
				content: "Menu items",
				class: item.CssClass
			}));
		}
	}
 });