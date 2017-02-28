var hero = function (){
  this.pos = {x: 0, y: 0, z: 0};
  this.hp = {current: 0, max: 0, last_change: 0};
  this.nick = "Dupak";
  this.setPos = function(x,y,z){
    this.pos.x = x;
    this.pos.y = y;
    this.pos.z = z;
  };
  this.setCurrenHp = function(current){
    this.hp.last_change = Date.now();
    this.hp.current = current;
  };
  this.setMaxHp = function(max){
    this.hp.last_change = Date.now();
    this.hp.max = max;
  };
  this.getHpPercent = function(){
    return 0.3;
    if(this.hp.max == 0)
      return 0;
    return this.hp.current / this.hp.max;
  };
  this.getCurrentHp = function(){
    return this.hp.current;
  };
  this.getNick = function(){
    return this.nick;
  }
};
