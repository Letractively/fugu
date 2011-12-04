db.fugu.users.remove();

db.fugu.users.insert({ Login:"yage", Password: "123", Email: "alexandr.lyalin@gmail.com", Role: 0, FirstName: "Alex", LastName: "Lyalin", About: "Key developer" })
db.fugu.users.insert({ Login:"dasha", Password: "123", Email: "dasha.lyalina@gmail.com", Role: 0, FirstName: "Dasha", LastName: "Lyalina", About: "Tester" })
db.fugu.users.insert({ Login: "anvar", Password: "123",  Role: 0, FirstName: "Pasha", LastName: "Semenov", About: "Designer" })

db.fugu.users.find().forEach(printjson);