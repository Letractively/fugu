self.importScripts('Box2D.js');




//Box2d aliases
var b2Vec2 = Box2D.Common.Math.b2Vec2;
var b2AABB = Box2D.Collision.b2AABB;
var b2BodyDef = Box2D.Dynamics.b2BodyDef;
var b2Body = Box2D.Dynamics.b2Body;
var b2FixtureDef = Box2D.Dynamics.b2FixtureDef;
var b2Fixture = Box2D.Dynamics.b2Fixture;
var b2World = Box2D.Dynamics.b2World;
var b2MassData = Box2D.Collision.Shapes.b2MassData;
var b2PolygonShape = Box2D.Collision.Shapes.b2PolygonShape;
var b2CircleShape = Box2D.Collision.Shapes.b2CircleShape;
var b2DebugDraw = Box2D.Dynamics.b2DebugDraw;
var b2MouseJointDef = Box2D.Dynamics.Joints.b2MouseJointDef;

//Create ground
//           Physics.CreateStaticBox({ halfWdth: 20, halfHeight: 2, posX: 10, posY: 400 / 30 + 1.8 });
//           Physics.CreateStaticBox({ halfWdth: 20, halfHeight: 2, posX: 10, posY: -1.8 });
//           Physics.CreateStaticBox({ halfWdth: 2, halfHeight: 14, posX: -1.8, posY: 13 });
//           Physics.CreateStaticBox({ halfWdth: 2, halfHeight: 14, posX: 21.8, posY: 13 });

//           for (i = 0; i < 15; i++) {
//               Physics.CreateDynamicBox(null);
//               Physics.CreateDynamicCircle(null);
//           }

//Physics.CreateDynamicBox({halfWdth: 1, halfHeight: 1, posX : 11, posY: 1 });
//Physics.CreateDynamicCircle({radius:1,posX:10, posY:7});

//tickTimerId = window.setInterval(TickHamdler, 1000 / 60);

// Start
//           ChangePhysicsState();

//           $("#canvas").mousemove(ShowCanvasCoords);

var Physics = {

    // Box2d physics world
    _world: null,
    _fixDef: null,
    _bodyDef: null,
    _intervalId: null,
    _config: null,
    _simulated: null,

    ReInit: function (config) {
		this._simulated = false;
        this._config = config;
        this._world = new Box2D.Dynamics.b2World(new b2Vec2(0, 10), true);
        this._bodyDef = new b2BodyDef;
        this._fixDef = new b2FixtureDef;
        this._fixDef.density = this._config.density ? this._config.density : 1.0;
        this._fixDef.friction = this._config.friction ? this._config.friction : 0.5;
        this._fixDef.restitution = this._config.restitution ? this._config.restitution : 0.2;

        if (this._config.canvas) {
            //Setup debug draw
            var debugDraw = new b2DebugDraw();
            debugDraw.SetSprite(this._config.canvas[0].getContext("2d"));
            debugDraw.SetDrawScale(30.0);
            debugDraw.SetFillAlpha(0.5);
            debugDraw.SetLineThickness(0.1);
            debugDraw.SetFlags(b2DebugDraw.e_shapeBit | b2DebugDraw.e_jointBit);
            this._world.SetDebugDraw(debugDraw);
        }
    },

    PauseResume: function (paused) {
        if (this._simulated == false)
            this._simulated = true;
        else
            this._simulated = false;
    },

    IsRunning: function () {
        return this._intervalId != null;
    },

    CreateBox: function (halfWdth, halfHeight, x, y) {
        this._fixDef.shape = new b2PolygonShape;
        this._fixDef.shape.SetAsBox(halfWdth ? halfWdth : Math.random() + 0.1, halfHeight ? halfHeight : Math.random() + 0.1);
        this._bodyDef.position.Set(x ? x : Math.random() * 10, y ? y : Math.random() * 10);
        return this._world.CreateBody(this._bodyDef).CreateFixture(this._fixDef);
    },

    CreateDynamicBox: function (desc) {
        this._bodyDef.type = b2Body.b2_dynamicBody;
        return desc ? this.CreateBox(desc.halfWdth, desc.halfHeight, desc.posX, desc.posY) : this.CreateBox(null, null, null, null);
    },

    CreateStaticBox: function (desc) {
        this._bodyDef.type = b2Body.b2_staticBody;
        return desc ? this.CreateBox(desc.halfWdth, desc.halfHeight, desc.posX, desc.posY) : this.CreateBox(null, null, null, null);
    },

    CreateCircle: function (radius, x, y) {
        this._fixDef.shape = new b2CircleShape(radius ? radius : Math.random() + 0.1);
        this._bodyDef.position.Set(x ? x : Math.random() * 10, y ? y : Math.random() * 10);
        return this._world.CreateBody(this._bodyDef).CreateFixture(this._fixDef);
    },

    CreateDynamicCircle: function (desc) {
        this._bodyDef.type = b2Body.b2_dynamicBody;
        return desc ? this.CreateCircle(desc.radius, desc.posX, desc.posY) : this.CreateCircle(null, null, null);
    },

    CreateStaticCircle: function (desc) {
        this._bodyDef.type = b2Body.b2_staticBody;
        return desc ? this.CreateCircle(desc.radius, desc.posX, desc.posY) : this.CreateCircle(null, null, null);
    },

	
	SetBodies: function(bodyEntities) {
		this._bodyDef.type = b2Body.b2_dynamicBody;
		for(var id in bodyEntities) {
			var entity = bodyEntities[id];
			if (entity.radius) {
				this._fixDef.shape = new b2CircleShape(entity.radius);
			} else {
				this._fixDef.shape = new b2PolygonShape;
				this._fixDef.shape.SetAsBox(entity.halfWidth, entity.halfHeight);
			}
		   this._bodyDef.position.x = entity.x;
		   this._bodyDef.position.y = entity.y;
		   this._bodyDef.userData = entity.id;
		   Physics._world.CreateBody(this._bodyDef).CreateFixture(this._fixDef);
		}
		this.ready = true;
	},

    // Processing simalution step
    Simulate: function (self) {

        if (Physics._simulated == true) {
            Physics._world.Step(1 / 60, 10, 10);
            if (Physics._config.canvas) {
                Physics._world.DrawDebugData();
            }
            Physics._world.ClearForces();
			Physics.SendUpdate();
        }
    },
	
	SendUpdate: function() {
		  var world = {};
			for (var b = Physics._world.GetBodyList(); b; b = b.m_next) {
				var userData = b.GetUserData();
				if(userData) {
					world[userData] = {x: b.GetPosition().x, y: b.GetPosition().y, a: b.GetAngle()};
				}
			  }
			postMessage(world);
	}
	
};

Physics.ReInit({ density: 1, friction: 0.5, restitution: 0.2 });			
Physics.CreateStaticBox({ halfWdth: 20, halfHeight: 2, posX: 10, posY: 700 / 30 + 1.8 });
Physics.CreateStaticBox({ halfWdth: 20, halfHeight: 2, posX: 10, posY: -1.8 });
Physics.CreateStaticBox({ halfWdth: 2, halfHeight: 14, posX: -1.8, posY: 13 });
Physics.CreateStaticBox({ halfWdth: 2, halfHeight: 14, posX: 31.8, posY: 13 });


var loop = function() {
    Physics.Simulate()
}
				
onmessage = function(e) {
    Physics.SetBodies(e.data);
	Physics.PauseResume();
	setInterval(loop, 1000 / 100);
};