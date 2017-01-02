var Communication = new (function(){
  var game = {};
  var objToSend = {};
  //JSBridge.callAfterUpdate = afterUpdate;
  function send(){
    return objToSend;
  }
  function isset(a){
    return typeof a != "undefined";
  }
  this.update = function(data){
    if(isset(data.hero) && !isset(game.hero)){
      game.hero={};
    }
    if(isset(data.hero.pos)){
      if(!isset(game.hero.pos)){
        game.hero.pos={};
      }
      game.hero.pos.x = data.hero.pos.x;
      game.hero.pos.y = data.hero.pos.y;
      game.hero.pos.z = data.hero.pos.z;
      ui.setHeroPos(game.hero.pos);
    }
    console.log(data);
  }
  this.getImg = function(id){
    return JSBridge.getImg(id);
  };

  this.moveUp = function(){
    JSBridge.move(1);
  }
  this.moveDown = function(){
    JSBridge.move(2);
  }
  this.moveLeft = function(){
    JSBridge.move(3);
  }
  this.moveRight = function(){
    JSBridge.move(4);
  }
  this.getPos = function(){

  }

})();
