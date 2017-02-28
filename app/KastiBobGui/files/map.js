var map = new(function () {
	var items = [];
	var grounds = [];
	var players = [];
	var showZ = 7; //true = all, numer = specific
	
	function updatePlayer(data){
		
	}
	
	function updateMap(data){
		
	}
	
	function drawMap(ctx, size){
		
	}
	
	this.start = function(com){
		Render.add(drawMap);
		com.registerUpdate("map", updateMap);
		com.registerUpdate("player", updatePlayer);
	};
})();