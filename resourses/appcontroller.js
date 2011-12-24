var AppController = {

	DynamicScript: function(id, script) {
		var head = document.getElementsByTagName("head")[0];			
		var script = document.createElement("script");
		script.type = "text/javascript";
		script.text = script;
		script.onload = function() {
			alert();
		};
		head.appendChild(script);
	},
	
	Loading: function(state) {
	},
	
	
	LoadView: function(viewName) {
		alert(viewName);
	}
}