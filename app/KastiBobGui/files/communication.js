var Communication = new (function(){
  JSBridge.callAfterUpdate = afterUpdate;
  function send(){

  }
  function afterUpdate(){
    console.log("variables was changed");
  }
  this.getImg = function(id){
    return false;
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
