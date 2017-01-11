var ui = new(function(){
  var walkDir={
    1: false,
    2: false,
    3: false,
    4: false
  };
  var showPanel = true;
  var walkCooldown = 0;
  var currTiles = [];
  this.moveUp = function(e){
    if(e==1){
      walkDir[1] = true;
    }else{
      walkDir[1] = false;
    }
  };
  this.moveDown = function(e){
    if(e==1){
      walkDir[2] = true;
    }else{
      walkDir[2] = false;
    }
  };
  this.moveLeft = function(e){
    if(e==1){
      walkDir[3] = true;
    }else{
      walkDir[3] = false;
    }
  };
  this.moveRight = function(e){
    if(e==1){
      walkDir[4] = true;
    }else{
      walkDir[4] = false;
    }
  };
  function moveDir(id){
    switch(id){
      case 1:return "moveUp";
      case 2:return "moveDown";
      case 3:return "moveLeft";
      case 4:return "moveRight";
    }
    return null;
  }
  function addTile(){
    
  }
  function delTile(){
    
  }
  this.setHeroPos = function(pos){
    var con = $("#heroPos");
    con.find(".posX").text(pos.x);
    con.find(".posY").text(pos.y);
    con.find(".posZ").text(pos.z);
  }
  function loop(){
    if(walkCooldown==0){
      var dir = null;
      if(walkDir[1]){
        dir = moveDir(1);
      }else if(walkDir[2]){
        dir = moveDir(2);
      }else if(walkDir[3]){
        dir = moveDir(3);
      }else if(walkDir[4]){
        dir = moveDir(4);
      }
      if(dir!==null){
        Communication[dir]();
        walkCooldown = 100;
      }
    }else{
      walkCooldown--;
    }
  };
  function hud(ctx, size){
    var mapWidth = size.width;
    if(showPanel){
      mapWidth -= 120;
      ctx.fillStyle = "black";
      ctx.fillRect(mapWidth, 0, 120, size.height);
    }
    ctx.fillStyle = "grey";
    ctx.fillRect(0, 0, mapWidth, size.height);
  }
  
  this.panelState = function(show){
    showPanel = show?true:false;
  }
  
  this.start = function(){
    setInterval(loop, 1);
    Render.add(hud);
    
  }

})();
