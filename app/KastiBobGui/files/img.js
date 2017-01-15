var Img = new(function(){
  var list = [];

  function download(id){
    console.log("comm");
    var binary = Communication.getImg(id);
    var new_img = new Image();
    new_img.src = "data:image/png;base64,"+binary;
    list[id] = new_img;
  }

  this.get = function(id){
    if(typeof list[id] == "undefined"){
      download(id);
    }
    return list[id];
  };

})();
