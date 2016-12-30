window.addEventListener("load", onload);
window.addEventListener("resize", onresize);

function reload(){
  window.location.reload();
}

function onload(){
  onresize();
  var need_files = ["render.js", "communication.js", "img.js", "console.js", "keys.js"];
  var $loading = $("<div>").addClass("loading").appendTo("body");
  var $log = $("<div>").appendTo($loading);
  var loading_files = 0;
  var loaded_files = 0;
  function log(txt){
    var $msg = $("<div>").text(txt).appendTo($log);
    return $msg;
  }
  function startLoading(path){
    loading_files++;
    var el = log("Loading "+path+"...");
    $.getScript("qrc:\\"+path, function(){
      loaded_files++;
      loading_files--;
      el.text(el.text()+"done");
      after_loading();
    });
  }
  function after_loading(){
    if(loading_files == 0 && loaded_files == need_files.length){
      $head_el.text($head_el.text()+"done");
      log("Starting...");
      start();
    }
  }
  function start(){
    try{
      //Render.start();
      $loading.remove();
      Keys.getNextKey(function(kcode, mod, key){
        Keys.registerHotkey(kcode, function(){alert("Key: "+mod+key)}, mod);
      });
    }catch(e){
      Console.error(e);
    }
  }
  var $head_el = log("Loading files...");
  for(var t in need_files){
    startLoading(need_files[t]);
  }
}

function onresize(){
  var h = window.innerHeight;
  var w = window.innerWidth;
  //document.body.style.width=w+"px";
  //document.body.style.height=h+"px";
}
