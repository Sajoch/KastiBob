var Communication = new (function(){
  var game = {};
  var objToSend = {};
  game.hero = new hero();
  var update_handlers = {};
  function send(){
    return objToSend;
  }
  function isset(a){
    return typeof a != "undefined";
  }
  function updateHero(data){
    if(isset(data.pos)){
      var d = data.pos;
      game.hero.setPos(d.x, d.y, d.z);
    }
    if(isset(data.hp)){
      game.hero.setCurrenHp(data.hp);
    }
    if(isset(data.maxhp)){
      game.hero.setMaxHp(data.maxhp);
    }
  }
  this.update = function(data){
    for(var t in data){
      for(var i in update_handlers[t]){
        update_handlers[t][i](data[t]);
      }
    }
  };
  this.registerUpdate = function(v, cb){
    if(typeof update_handlers[v] == "undefined"){
      update_handlers[v] = [];
    }
    update_handlers[v].push(cb);
    return true;
  };
  this.unregisterUpdate = function(v, cb){
    if(typeof update_handlers[v] == "undefined")
      return false;
    var idx = update_handlers[v].indexOf(cb);
    if(idx == -1)
      return false;
    update_handlers[v].splice(idx, 1);
    return true;
  };
  this.getImg = function(id){
    return JSBridge.getImg(id);
  };
  this.move = {};
  this.move.up = function(){
    JSBridge.move(1);
  };
  this.move.down = function(){
    JSBridge.move(2);
  };
  this.move.left = function(){
    JSBridge.move(3);
  };
  this.move.right = function(){
    JSBridge.move(4);
  };
  this.getGame = function(){
    return game;
  };
  this.start = function(){
    this.registerUpdate("hero", updateHero);
    JSBridge.start();
  };

})();
