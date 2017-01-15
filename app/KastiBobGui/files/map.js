var map = new(function () {
	
	function updateMap(data){
		
	}
	
	function drawMap(ctx, size){
		
	}
	
	this.start = function(com){
		Render.add(drawMap);
		com.registerUpdate("map", updateMap);
	};
})();