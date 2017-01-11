var Img = new(function(){
  var list = [];

  function download(id){
    var binary = Communication.getImg(id);
    var dimg = Render.createImage(32, 32);
    var di = 0;
    var bi = binary.split("");
    
    for(var i=0;i<bi.length;i++){
      dimg.data[i] = bi[i].charCodeAt(0);
    }
    list[id] = dimg;
  }

  this.get = function(id){
    if(typeof list[id] == "undefined"){
      download(id);
    }
    return list[id];
  };

})();
