var Render = new (function(){
  var list = [];
  var running = false;
  var index;
  var ctx = null;
  var size = {height: 0, width: 0};
  var game = null;
  function render(){
    for(index = 0;index<list.length;index++){
      list[index](ctx, size);
    }
    if(running)
      requestAnimationFrame(render);
  }

  this.add = function(draw_func){
    if(list.indexOf(draw_func) == -1)
      list.push(draw_func);
  };

  this.del = function(draw_func){
    var idx = list.indexOf(draw_func);
    if(idx != -1){
      list.splice(idx, 1);
    }
  };

  this.start = function(){
    if(running) return;
    running = true;
    game = document.getElementById("game");
    size.height = game.height;
    size.width = game.width;
    ctx = game.getContext("2d");
    if(ctx === null){
      running = false;
    }else{
      render();
    }
  };

  this.stop = function(){
    if(!running) return;
    running = false;
  };
  
  this.resize = function(w, h){
    if(game === null){
      return;
    }
    game.width = w;
    game.height = h;
    size.height = game.height;
    size.width = game.width;
  }
  
  this.createImage = function(w, h){
    return ctx.createImageData(w, h);
  }

})();
