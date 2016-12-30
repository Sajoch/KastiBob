var Render = new (function(){
  var list = [];
  var running = false;
  var index;
  var ctx = null;
  function render(){
    index = 0;
    for(;index<list.length;index++)
      list[index](ctx);
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
    var game = document.getElementById("game");
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

})();
