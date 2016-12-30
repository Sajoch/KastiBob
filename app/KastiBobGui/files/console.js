var Console = new(function(){
  var $console = null;
  var open = false;
  $console = $("<div>").addClass("console").appendTo("body");

  function log(tab){
    var $el = $("<div>").appendTo($console);
    for(var t=0;t<tab.length;t++){
      var $txt = $("<span>").text(tab[t]).appendTo($el);
    }
  }

  function show(){
    open = true;
    $console.fadeIn(200);
  }

  function hide(){
    open = false;
    $console.fadeOut(200);
  }

  this.toggle = function(){
    if(open) hide();
    else show();
  };

  this.log = function(){
    log(arguments);
  };

  this.error = function(){
    log(arguments);
    show();
  };

})();
