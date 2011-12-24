db.fugu.views.remove();

db.fugu.views.insert({ Name:"testview1"})
db.fugu.views.insert({ Name:"testview2"})

db.fugu.views.find().forEach(printjson);