if (!Function.prototype.Bind) { // check if native implementation available
  Function.prototype.Bind = function() { 
	var fn = this, args = Array.prototype.slice.call(arguments),
	object = args.shift(); 
	return function() { 
		return fn.apply(object, args.concat(Array.prototype.slice.call(arguments))); 
	}; 
  };
}

/* Simple JavaScript Inheritance
 * By John Resig http://ejohn.org/
 * MIT Licensed.
 */
// Inspired by base2 and Prototype
(function(){
  var initializing = false, fnTest = /xyz/.test(function(){xyz;}) ? /\b_base\b/ : /.*/;
  // The base Class implementation (does nothing)
  this.Class = function(){};
  
  // Create a new Class that inherits from this class
  Class.extend = function(prop) {
    var _base = this.prototype;
    
    // Instantiate a base class (but only create the instance,
    // don't run the init constructor)
    initializing = true;
    var prototype = new this();
    initializing = false;
    
    // Copy the properties over onto the new prototype
    for (var name in prop) {
      // Check if we're overwriting an existing function
      prototype[name] = typeof prop[name] == "function" && 
        typeof _base[name] == "function" && fnTest.test(prop[name]) ?
        (function(name, fn){
          return function() {
            var tmp = this._base;
            
            // Add a new ._base() method that is the same method
            // but on the super-class
            this._base = _base[name];
            
            // The method only need to be bound temporarily, so we
            // remove it when we're done executing
            var ret = fn.apply(this, arguments);        
            this._base = tmp;
            
            return ret;
          };
        })(name, prop[name]) :
        prop[name];
    }
    
    // The dummy class constructor
    function Class() {
      // All construction is actually done in the init method
      if ( !initializing && this.Ctor )
        this.Ctor.apply(this, arguments);
    }
    
    // Populate our constructed prototype object
    Class.prototype = prototype;
    
    // Enforce the constructor to be what we expect
    Class.prototype.constructor = Class;

    // And make this class extendable
    Class.extend = arguments.callee;
    
    return Class;
  };
})();

function BlockPanel(panel) {
	$(panel).css('overflow', 'hidden');
	$(panel).block({ css: {
		border: 'none'
		,backgroundColor: '#000'
		,'border-radius': '10px 10px 10px 10px'
		,opacity: 0.5
		,color: '#fff'
		,'margin-top':'40%'
		,'margin-left':'35%'
	} }); 
}

function UnblockPanel(panel) {
	$(panel).unblock(); 
	$(panel).css('overflow', 'auto');
}

function DynamicScript(id, script) {
	var head = document.getElementsByTagName("head")[0];			
	var script = document.createElement("script");
	script.type = "text/javascript";
	script.text = script;
	script.onload = function() {
		alert();
	};
	head.appendChild(script);
}

function SetCookie(name,value,days) {
	if (days) {
		var date = new Date();
		date.setTime(date.getTime()+(days*24*60*60*1000));
		var expires = "; expires="+date.toGMTString();
	}
	else var expires = "";
	document.cookie = name+"="+value+expires+"; path=/";
}

function GetCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}

function EraseCookie(name) {
	SetCookie(name,"",-1);
}