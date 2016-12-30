var Img = new(function(){
  var list = [];

  function download(id){
    list[id] = communication.getImg(id);
  }

  this.get = function(id){
    if(typeof list[id] == "undefined"){
      download(id);
    }
    return list[id];
  };

})();
