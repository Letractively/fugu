if (!Function.prototype.bind) { // check if native implementation available
  Function.prototype.bind = function(){ 
    var fn = this, args = Array.prototype.slice.call(arguments),
        object = args.shift(); 
    return function(){ 
      return fn.apply(object, 
        args.concat(Array.prototype.slice.call(arguments))); 
    }; 
  };
}

var AppController = Class.extend({
	// Create tabs by div
	CreateNavigation: function(tabsDiv) {
		this.tabs = tabsDiv.tabs({ select: this._HandleSelectTab.bind(this) });
	},
	
	_HandleSelectTab: function(event, ui) {
		$(ui.panel).css('overflow', 'hidden');
		$(ui.panel).block({ css: {
			border: 'none'
			,backgroundColor: '#000'
			,'border-radius': '10px 10px 10px 10px'
			,opacity: 0.5
			,color: '#fff'
			,'margin-top':'40%'
			,'margin-left':'35%'
		} }); 
		
		setTimeout(function() { 
			$(ui.panel).unblock(); 
			$(ui.panel).css('overflow', 'auto');
		}, 2000); 
	},
	
	CreateContentSizeAdjuster: function() {
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
	
	DynamicScript: function(id, script) {
		var head = document.getElementsByTagName("head")[0];			
		var script = document.createElement("script");
		script.type = "text/javascript";
		script.text = script;
		script.onload = function() {
			alert();
		};
		head.appendChild(script);
	}
});