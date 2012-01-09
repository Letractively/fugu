var ViewsEditorTab = ContentTab.extend({

	_columns: ["Name", "Description"],
	
	Ctor: function(panel) {
		this._base(panel);
		this._element.addClass("contain");
	},
	
	Select: function() {
		BlockUI(this._panel);
		this._base();
		$.ajax({
		  type: 'POST',
		  url: "/getallviews",
		  data: "",
		  dataType: "json"
		})
		.success(function(data) {
			this.Refresh(data.Json);
			
		}.Bind(this))
		.error(function(err) { alert("Error: " + err); })
		.complete(function() { UnblockUI(this._panel); }.Bind(this));
	},
	
	Leave: function() { return true; },
	
	Refresh: function(views) {
		this._views = views ;
		
		this._element.empty();
		this._element.addClass("ui-widget");
		var table = "<table class='ui-widget ui-widget-content'><thead><tr class='ui-widget-header'>";
		table += "<th width='40px'></th><th width='40px'></th>";
		
		for(var i=0; i< this._columns.length; i++)
			table += "<th>" + this._columns[i] + "</th>";
		table += "</tr></thead><tbody>";
		
		for(var i=0; i< this._views.length; i++) {
			table += "<tr>";
			table += "<td><input id='" + i + "' type='button' value='D'/></td>";
			table += "<td><input id='" + i + "' type='button' value='E'/></td>";
			for(var j=0; j < this._columns.length; j++) {
				var field = this._views[i][this._columns[j]];
				if(field)
					table += "<td>" + field.toString() + "</td>";
				else
					table += "<td></td>";
			}
			table += "</tr>"
		}
		table += "</tbody></table>";
		
		$("<h3>Existing Views:</h3>").appendTo(this._element);
		this._viewsTable = $(table).appendTo(this._element);
		this._CreateButtons();
	},
	
	_CreateButtons: function() {
		var self = this;
		$("input:button[value='D']", this._viewsTable).button().click(function() {
			var view = self._views[this.id];
			Confrim(null, function(yes) {
				if(yes) {
						BlockUI();
						var data = '{ViewName: "'+ view.Name + '"}';
						$.ajax({
						  type: 'POST',
						  url: "/deleteview",
						  data: data,
						  dataType: "json"
						})
						.success(function(data) {
							self.Refresh(data.Json);
							
						}.Bind(this))
						.error(function(err) { alert("Error: " + err); })
						.complete(function() { UnblockUI(); }.Bind(this));
		
				}
			});
		});
		$("input:button[value='E']", this._viewsTable).button().click(function() { self._OpenViewDialog(this.id); });
		$("<button>Create new view</button>").button().appendTo(this._element).click(function() { self._OpenViewDialog(-1); });
	},
	
	_OpenViewDialog: function (viewId) {
		var view = this._views[viewId];
		
		var dialog = $("<div style='display:none'></div>").appendTo(this._element);
		$("<label>Name:</label><br/>").appendTo(dialog);
		var name = $("<input style='width:99%'></input>").appendTo(dialog);
		if(view) name.val(view["Name"]);
			
		$("<br/><label>Content:</label><br/>").appendTo(dialog);
		var content = $("<textarea rows='10' cols='120'></textarea>").appendTo(dialog);
		if(view) content.val(view["Content"]);
		
		$("<br/><label>Javascript:</label><br/>").appendTo(dialog);
		var js = $("<textarea rows='10' cols='120'></textarea>").appendTo(dialog);
		if(view) js.val(view["JavaScript"]);
		
		dialog = $(dialog).dialog({
			title:"Views editor",
			modal: true,
			width: 'auto',
			height: 'auto',
			resizable: false,
			position: 'center',
			buttons: {
				"Save": function() {
				
					if((!view) && this._HasView(name.val())) {
						alert("View already exists");
					}
					else {
						if(!view){
							view = {};
							this._views.push(view);
						}
						view["Name"] = name.val();
						view["Content"] = content.val();
						view["JavaScript"] = js.val();
						this.Refresh(this._views);
						
						this.SaveView(view);
						
						$(dialog).dialog("close");
						$(dialog).empty();
					}
				}.Bind(this), 
				"Cancel": function() { 
					$(dialog).dialog("close"); 
					$(dialog).empty();
				}.Bind(this) 
			}
		});
	},
	
	_HasView: function(name) {
		for(var i=0; i< this._views.length; i++) {
			if(this._views[i].Name == name) return true;
		}
		return false;
	},
	
   SaveView: function(view) {
		BlockUI();
		var json_text = JSON.stringify(view);
		$.ajax({
		  type: 'POST',
		  url: "/saveview",
		  data: json_text,
		  dataType: "json"
		})
		.success(function(data) {})
		.error(function(error) { alert("Error:" + error);})
		.complete(function() { UnblockUI();})
   }
});