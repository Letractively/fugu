dojo.require("dijit._Widget");
dojo.require("dijit._Templated");
dojo.require("dijit.layout.ContentPane");

dojo.declare("HeaderView", [dijit.layout.ContentPane], {	
	constructor: function(args){
		dojo.safeMixin(this, args);
		this.style = "background-image:url(fugu/images/header.png);height:4%;border-radius:10px 10px 10px 10px;";
		this.region = "top";
		this.class = "edgePanel";
	}
});