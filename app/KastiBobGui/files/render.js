var Render = new (function(){
  var list = [];
  var running = false;
  var index;
  var ctx = null;
  var size = {height: 0, width: 0};
  var game = null;
  var divider = 1;
  var frame_state = 0;
  function render(){
    for(index = 0;index<list.length;index++){
      list[index](ctx, size);
    }
    requestAnimationFrame(render);
  }

  function renderDiv(){
    frame_state++;
    if(frame_state >= divider){
      frame_state = 0;
      for(index = 0;index<list.length;index++){
        list[index](ctx, size);
      }
    }
    requestAnimationFrame(renderDiv);
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

  this.start = function(div){
    if(running) return;
    running = true;
    div = div || false;
    game = document.getElementById("game");
    size.height = game.height;
    size.width = game.width;
    ctx = game.getContext("2d");
    if(ctx === null){
      running = false;
    }else{
      if(div){
        renderDiv();
      }else{
        render();
      }
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

  this.setDivider = function(a){
    divider = a;
  }

})();
