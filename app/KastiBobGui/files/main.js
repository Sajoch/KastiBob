window.addEventListener("load", onload);
window.addEventListener("resize", onresize);

function onload(){
  onresize();
  var game = document.getElementById("game");
  var ctx = game.getContext("2d");
  ctx.fillStyle="black";
  //ctx.fillRect(0, 0, 600, 600);
}

function onresize(){
  var h = window.innerHeight;
  var w = window.innerWidth;
  document.body.style.width=w+"px";
  document.body.style.height=h+"px";
}
