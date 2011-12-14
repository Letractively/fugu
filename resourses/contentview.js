dojo.require("dijit.Editor");
dojo.require("dijit.form.TextBox");
dojo.require("dijit.form.Button");
dojo.require("dijit._Widget");
dojo.require("dijit._Templated");
dojo.require("dijit.dijit");
dojo.require("dojox.layout.TableContainer");


dojo.declare("ContentView",[dijit._Widget,dijit._Templated],{
	templateString: "<div>"
					+ "<button dojoType='dijit.form.Button' type='button' dojoAttachEvent='ondijitclick:SaveView'>Save</button>" 
					+ "<button dojoType='dijit.form.Button' type='button' dojoAttachEvent='ondijitclick:LoadView'>Load</button>" 
					+"<input dojoAttachPoint='viewName' type='text' style='width:100%'/>"
					+"<textarea dojoAttachPoint='viewContent' style='width:100%'></textarea >"
					+"</div>",
				
	constructor: function(args) {
		dojo.safeMixin(this, args);
		this.id = "appContent";
		this.style="border-radius:10px 10px 10px 10px";
		this.region = "center";
		this.splitter = false;
		this.gutter = false;
		this.class = "edgePanel";
	},
	
	LoadView: function(){
		var xhrArgs = {
			postData: "myform",
			handleAs: "text/json",
			load: function(data) {
			},
			error: function(error) {
			}
		}
		//Call the asynchronous xhrPost
		var deferred = dojo.xhrPost(xhrArgs);
	},
	
	SaveView: function(){

		var xhrArgs = {
			url: "/dbview.fsp",
			putData: "{ 'Name': '"+ this.viewName.value +"', 'Content' : '"+ this.viewContent.value +"', 'Region':'', 'JavaScript':'' }",
			handleAs: "text",
			load: function(data) {
				controller.Loading(false);
			},
			error: function(error) {
				controller.Loading(false);
			}
		}
		
		controller.Loading(true);
		//Call the asynchronous xhrPost
		var deferred = dojo.xhrPut(xhrArgs);
	},
	
    postCreate: function(){
		//var editor = new dijit.Editor({plugins: ["bold","italic","|","cut","copy","paste","|","insertUnorderedList"]}, this.jsBody);
    },
	
    startup: function(){
        // This fires after my children are available
    }
});