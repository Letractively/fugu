dojo.require("dijit.Editor");
dojo.require("dijit.form.TextBox");
dojo.require("dijit.form.Button");
dojo.require("dijit._Widget");
dojo.require("dijit._Templated");
dojo.require("dijit.dijit");
dojo.require("dojox.layout.TableContainer");


dojo.declare("ContentView",[dijit._Widget,dijit._Templated],{
	templateString: "<div>"
					+ "<button dojoType='dijit.form.Button' type='button' dojoAttachEvent='ondijitclick:SaveJS'>Save</button>" 
					+"<input dojoAttachPoint='jsName' type='text' style='width:100%'/>"
					+"<textarea dojoAttachPoint='jsBody' style='width:100%'></textarea >"
					+"</div>",
				
	constructor: function(args){
		dojo.safeMixin(this, args);
		this.style="border-radius:10px 10px 10px 10px";
		this.region = "center";
		this.splitter = false;
		this.gutter = false;
		this.class = "edgePanel";
	},
	
    postCreate: function(){
		//var editor = new dijit.Editor({plugins: ["bold","italic","|","cut","copy","paste","|","insertUnorderedList"]}, this.jsBody);
    },
	SaveJS: function(){
		alert(this.jsBody.value);
	},
    startup: function(){
        // This fires after my children are available
    }
});

/*
dojo.declare("ContentView", [ dojox.layout.TableContainer ], {
	region: "center",
	class:"edgePanel",
	style:"border-radius:10px 10px 10px 10px;",
	cols: 2,
	
	constructor: function(args){
		dojo.safeMixin(this, args);
		var editor = new dijit.Editor({plugins: ["bold","italic","|","cut","copy","paste","|","insertUnorderedList"]});
		this.addChild(editor);
	},
	
	postCreate: function() {
	}
});
*/

/*
dojo.declare("ContentView", [dijit.layout.ContentPane], {
 
	constructor: function(args){
		dojo.safeMixin(this, args);
		this.style="border-radius:10px 10px 10px 10px;";
		this.region = "center";
		this.splitter = false;
		this.gutter = false;
		this.class = "edgePanel";
		this.content="<button id='saveStoreBtn' dojoType='dijit.form.Button' type='button'>Save</button>"
					+ "<input id='storedJsId' type='text' style='width:100%' dojoType='dijit.form.TextBox'/>"
					+ "<div data-dojo-type='dijit.Editor'></div>";
	},
	
	postCreate: function() {
	
		dojo.connect(dojo.byId("saveStoreBtn"),"onclick", function() {
			alert("");
		});

        //var editor = new dijit.Editor({
           // plugins: ["bold","italic","|","cut","copy","paste","|","insertUnorderedList"]
       // });
		
		//editor.placeAt(this);
	}
});
*/