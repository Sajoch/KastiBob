var ui = new(function () {
	var walkDir = {
		1: false,
		2: false,
		3: false,
		4: false
	};
	var show_panel = true;
	var registered_calls = [];
	var currTiles = [];
	var last_hpp = 0;
	var sidePanel = null;
	var panelElements = [];
	var move_dir = {
		1: "up",
		2: "down",
		3: "left",
		4: "right"
	};
	this.moveUp = function (e) {
		if (e == 1) {
			walkDir[1] = true;
		} else {
			walkDir[1] = false;
		}
	};
	this.moveDown = function (e) {
		if (e == 1) {
			walkDir[2] = true;
		} else {
			walkDir[2] = false;
		}
	};
	this.moveLeft = function (e) {
		if (e == 1) {
			walkDir[3] = true;
		} else {
			walkDir[3] = false;
		}
	};
	this.moveRight = function (e) {
		if (e == 1) {
			walkDir[4] = true;
		} else {
			walkDir[4] = false;
		}
	};

	function registerLoop(delay, func) {
		var obj = {
			next: 0,
			delay: delay,
			func: func
		};
		registered_calls.push(obj);
		return obj;
	}

	function loop() {
		var now = Date.now();
		for (var t in registered_calls) {
			var o = registered_calls[t];
			if (o.next <= now) {
				if (o.func())
					o.next = now + o.delay;
			}
		}
	};
	
	function initPanel(){
		$("<div>").addClass("nickname").appendTo(sidePanel);
		var pos = $("<div>").addClass("position").appendTo(sidePanel);
		$("<div>").addClass("pos_x").appendTo(pos);
		$("<div>").addClass("pos_y").appendTo(pos);
		$("<div>").addClass("pos_z").appendTo(pos);
		sidePanel.find(".nickname").text("Nickname");
		sidePanel.find(".position .pos_x").text("X");
		sidePanel.find(".position .pos_y").text("Y");
		sidePanel.find(".position .pos_z").text("Z");
	}

	function hpColor(percent) {
		var r = (255 - (255 * percent)) & 0xff;
		var g = (255 * percent) & 0xff;
		var b = 0;
		return "rgb(" + r + "," + g + "," + b + ")";
	}

	this.panelState = function (show) {
		show_panel = show ? true : false;
		if(show_panel){
			sidePanel.show();
		}else{
			sidePanel.hide();
		}
	}

	this.start = function () {
		setInterval(loop, 1);
		sidePanel = $("#side");
		initPanel();
		registerLoop(100, function () {
			for (var t in move_dir) {
				if (walkDir[t]) {
					Communication.move[move_dir[t]]();
					return true;
				}
			}
			return false;
		});

	}

})();