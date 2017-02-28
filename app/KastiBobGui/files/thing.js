var thing = new(function(){
	var comm = null;
	
	this.getItem = function(id){
		return new Item(comm.getDatObject(1, id));
	};
	this.getOutfit = function(id){
		//return new Item(comm.getDatObject(2, id));
	};
	
	this.start = function(c){
		comm = c;
	}
})();