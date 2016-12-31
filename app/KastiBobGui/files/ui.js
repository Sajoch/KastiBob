var ui = new(function(){
  var walkDir={
    1: false,
    2: false,
    3: false,
    4: false
  };
  var walkCooldown = 0;
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
  this.loop = function(){
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

})();
