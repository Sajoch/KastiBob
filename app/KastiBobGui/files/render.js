var Render = new (function(){
  var list = [];
  var running = false;
  var index;
  var ctx = null;
  var size = {height: 0, width: 0};
  var game = null;
  var ops_interval = null;
  var need_to_clear = false;
  var cached_txt_size = [];

  function caller(){
    if(need_to_clear){
      ctx.clearRect(0,0,size.height,size.width);
      need_to_clear = false;
    }
    for(index = 0;index<list.length;index++){
      list[index](ctx, size);
    }
  }

  function render(){
    caller();
    if(running)
      requestAnimationFrame(render);
  }

  this.clear = function(){
    //clearRect before next caller
    need_to_clear = true;
  }

  this.add = function(draw_func){
    if(list.indexOf(draw_func) == -1){
      list.push(draw_func);
      return true;
    }
    return false;
  };

  this.del = function(draw_func){
    var idx = list.indexOf(draw_func);
    if(idx != -1){
      list.splice(idx, 1);
      return true;
    }
    return false;
  };

  this.start = function(ops){
    //ops = true - 1 call per second, false - call by requestAnimationFrame
    if(running) return;
    running = true;
    ops = ops || false;
    game = document.getElementById("game");
    size.height = game.height;
    size.width = game.width;
    ctx = game.getContext("2d");
    if(ctx === null){
      running = false;
    }else{
      if(ops){
        ops_interval = setInterval(caller, 1000);
      }else{
        render();
      }
    }
  };

  this.stop = function(){
    if(!running) return;
    running = false;
    if(ops_interval !== null){
      clearInteval(ops_interval);
      ops_interval = null;
    }
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
  };
  
  this.getTextSize = function(txt, width, height){
    if(typeof cached_txt_size[txt] == "undefined"){
      cached_txt_size[txt] = [];
    }
    if(typeof cached_txt_size[txt][width] == "undefined"){
      cached_txt_size[txt][width] = [];
    }
    if(typeof cached_txt_size[txt][width][height]== "undefined"){
      cached_txt_size[txt][width][height] = [];
    }else{
      return cached_txt_size[txt][width][height];
    }
    var data = '<svg xmlns="http://www.w3.org/2000/svg" width="'+width+'" height="'+height+'">' +
           '<foreignObject width="100%" height="100%">' +
           '<div style="font-size:'+height+'px">' +
             txt +
           '</div>' +
           '</foreignObject>' +
           '</svg>';
    var DOMURL = window.URL || window.webkitURL || window;
    var img = new Image();
    var svg = new Blob([data], {type: 'image/svg+xml'});
    var url = DOMURL.createObjectURL(svg);
    img.onload = function () {
      DOMURL.revokeObjectURL(url);
    }
    img.src = url;
    cached_txt_size[txt][width][height] = img;
    return img;
  };

})();
