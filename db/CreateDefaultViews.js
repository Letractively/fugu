db.fugu.views.remove();

db.fugu.views.insert({ 
Name: "masterpage", 
Content: "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01//EN' 'http://www.w3.org/TR/html4/strict.dtd'>\r\n\
<html dir='ltr'>\r\n\
<head>\r\n\
	<title>fugu</title>\r\n\
	<link rel='stylesheet' type='text/css' href='jquery-ui/css/hot-sneaks/jquery-ui-1.8.16.custom.css'/>\r\n\
	<script type='text/javascript' src='jquery-1.6.2.min.js'></script>\r\n\
	<script type='text/javascript' src='jquery.blockUI.js'></script>\r\n\
	<script type='text/javascript' src='jquery-ui/js/jquery-ui-1.8.16.custom.min.js'></script>\r\n\
	<link rel='stylesheet' type='text/css' href='css/fugu.css'/>\r\n\
	<script type='text/javascript' src='common.js'></script>\r\n\
	<script type='text/javascript' src='contentmgr.js'></script>\r\n\
	<script type='text/javascript' src='viewseditor.js'></script>\r\n\
	<script type='text/javascript'>\r\n\
		$(document).ready(function () {\r\n\
            tabs = new ContentManager($('#tabs'), null);\r\n\
		});\r\n\
	</script>\r\n\
</head>\r\n\
<body>\r\n\
<div id='container'>\r\n\
		<div id='tabs'>\r\n\
			<ul>\r\n\
				<li><a href='#home'>Home</a></li>\r\n\
				<li><a href='#play'>Play</a></li>\r\n\
				<li><a href='#editor'>Editor</a></li>\r\n\
				<li><a href='#forum'>Forum</a></li>\r\n\
				<li><a href='#profile'>Login</a></li>\r\n\
                <li><a href='#viewseditor'>Views editor</a></li>\r\n\
                <li><a href='#users'>Users</a></li>\r\n\
			</ul>\r\n\
			<div id='home' class='ui-widget ui-widget-content'>\r\n\
				<p>Proin elit arcu, rutrum commodo, vehicula tempus, commodo a, risus. Curabitur nec arcu. Donec sollicitudin mi sit amet mauris. Nam elementum quam ullamcorper ante. Etiam aliquet massa et lorem. Mauris dapibus lacus auctor risus. Aenean tempor ullamcorper leo. Vivamus sed magna quis ligula eleifend adipiscing. Duis orci. Aliquam sodales tortor vitae ipsum. Aliquam nulla. Duis aliquam molestie erat. Ut et mauris vel pede varius sollicitudin. Sed ut dolor nec orci tincidunt interdum. Phasellus ipsum. Nunc tristique tempus lectus.</p>\r\n\
			</div>\r\n\
			<div id='play'>\r\n\
				<p>Morbi tincidunt, dui sit amet facilisis feugiat, odio metus gravida ante, ut pharetra massa metus id nunc. Duis scelerisque molestie turpis. Sed fringilla, massa eget luctus malesuada, metus eros molestie lectus, ut tempus eros massa ut dolor. Aenean aliquet fringilla sem. Suspendisse sed ligula in ligula suscipit aliquam. Praesent in eros vestibulum mi adipiscing adipiscing. Morbi facilisis. Curabitur ornare consequat nunc. Aenean vel metus. Ut posuere viverra nulla. Aliquam erat volutpat. Pellentesque convallis. Maecenas feugiat, tellus pellentesque pretium posuere, felis lorem euismod felis, eu ornare leo nisi vel felis. Mauris consectetur tortor et purus.</p>\r\n\
			</div>\r\n\
			<div id='editor'></div>\r\n\
			<div id='forum' class='content'></div>\r\n\
            <div id='profile' class='content'></div>\r\n\
            <div id='viewseditor'></div>\r\n\
            <div id='users'></div>\r\n\
		</div>\r\n\
</div>\r\n\
</body>\r\n\
</html>",
JavaScript: "" })

db.fugu.views.find().forEach(printjson);