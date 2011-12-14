dojo.require("dijit.layout.AccordionContainer");
dojo.require("dijit.layout.BorderContainer");
dojo.require("dijit.layout.LayoutContainer");
dojo.require("dijit.layout.ContentPane");
dojo.require("dojo.html");
dojo.require("dijit.MenuBar");
dojo.require("dijit.Menu");
dojo.require("dijit.MenuItem");
dojo.require("dijit.layout.ContentPane");
dojo.require("dojox.widget.Standby");
dojo.require("dojo.parser");

dojo.declare("AppController", null, {
	_standby: null,
	_appLayout: null,
	
	constructor: function(args){
		dojo.safeMixin(this, args);
	},
	
	CreateUI: function() {
		this.CreateLayout();
		this.CreateStandBy();
	},
	
	CreateLayout: function() {
		this._appLayout = new dijit.layout.BorderContainer({
			id: "appLayout",
			class: "demoLayout",
			style: "height: 100%;"
		});
		
		this.AddContainer(new HeaderView());
		this.AddContainer(new MenuView());
		this.AddContainer(new ContentView());
		
		this._appLayout.placeAt(dojo.body());
		this._appLayout.startup();
	},
	
	AddContainer: function(container) {
		this._appLayout.addChild(container);
		container.startup();
	},
	
	CreateStandBy: function() {
		this._standby = new dojox.widget.Standby({
			target: "appContent",
			image: "fugu/images/busy.gif"
		});
		
		document.body.appendChild(this._standby.domNode);
		this._standby.startup();
	},
	
	LoadContentView: function (viewName) {
		var viewurl = "fugu/views/"+viewName+".js";
		var self = this;
		this.Loading(true);
		dojo.xhrGet({
			url:viewurl,
			handleAs:"text",
			load: function(response){
				var head = document.getElementsByTagName("head")[0];
				
				var script = document.createElement("script");
				script.type = "text/javascript";
				script.text = response;
				script.onload = function() {
					alert();
				};
				head.appendChild(script);
							
				self.Loading(false);
			}
		});
	},
	
	Loading: function(state) { 
		if(state) this._standby.show();
		else this._standby.hide();
	}
	
});
	
dojo.addOnLoad(function () {
	controller = new AppController();
	controller.CreateUI();
});