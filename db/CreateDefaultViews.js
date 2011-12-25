db.fugu.views.remove();

db.fugu.views.insert({ Name:"testview1", Content: "<h1>Hello world</h1>"})
db.fugu.views.insert({ Name:"testview2", Content: "<h1>Hello worl2</h1>"})

db.fugu.views.find().forEach(printjson);