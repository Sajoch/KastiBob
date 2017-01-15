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
	var move_dir = {
		1: "up",
		2: "down",
		3: "left",
		4: "right"
	};
	var nick_calcs = null;
	var font = "Arial";
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

	function addTile() {

	}

	function delTile() {

	}

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

	function hud(ctx, size) {
		var map_width = size.width;
		if (show_panel) {
			var panel_width = Math.max(120, size.width * 0.15);
			var hp_arc_radius = panel_width * 0.42;
			var wpanel_padding = Math.max(5, panel_width * 0.05);
			var hpanel_padding = Math.max(5, size.height * 0.008);
			map_width -= panel_width;
			ctx.fillStyle = "green";
			ctx.fillRect(map_width, 0, panel_width, size.height);
			var elementY = 0;
			elementY += (panel_width / 2);
			drawHp(ctx, map_width + (panel_width / 2), elementY, hp_arc_radius);
			elementY += hpanel_padding;
			drawNick(ctx, 
        map_width + wpanel_padding, 
        elementY, panel_width - 2 * wpanel_padding, 
        4 * hpanel_padding);
			elementY += 5 * hpanel_padding;

		}
		ctx.fillStyle = "grey";
		ctx.fillRect(0, 0, map_width, size.height);
	}

	function hpColor(percent) {
		var r = (255 - (255 * percent)) & 0xff;
		var g = (255 * percent) & 0xff;
		var b = 0;
		return "rgb(" + r + "," + g + "," + b + ")";
	}

	function drawHp(ctx, x, y, r) {
		var hpp = Communication.getGame().hero.getHpPercent();
		//holder
		ctx.beginPath();
		ctx.fillStyle = "grey";
		ctx.strokeStyle = "white";
		ctx.moveTo(x, y);
		ctx.lineTo(x + r, y);
		ctx.arc(x, y, r, 0, Math.PI, true);
		ctx.lineTo(x, y);
		ctx.fill();
		ctx.stroke();

		//current val
		var endAngle = Math.PI + (hpp * Math.PI);
		ctx.beginPath();
		ctx.fillStyle = hpColor(hpp);
		ctx.moveTo(x, y);
		ctx.lineTo(x - r, y);
		ctx.arc(x, y, r, Math.PI, endAngle, false);
		ctx.lineTo(x, y);
		ctx.fill();
	}

  function ellipsisText(ctx, txt, width, font){
    ctx.font = font;
    var w, ret_txt;
    w = ctx.measureText(txt).width;
    if(w<width){
      return txt;
    }
    while(w>width){
      txt = txt.substr(0, txt.length-1);
      ret_txt = txt+"…";
      w = ctx.measureText(ret_txt).width;
    }
    return ret_txt;
  }

	function drawNick(ctx, x, y, width, height) {
		var nick = "Kiris to nie jest pan"; //Communication.getGame().hero.getNick();
		ctx.beginPath();
		ctx.strokeStyle = "black";
		ctx.fillStyle = "grey";
		ctx.rect(x, y, width, height);
		ctx.fill();
		ctx.stroke();
    ctx.drawImage(Render.getTextSize(nick, width, height), x, y);
	}

	this.panelState = function (show) {
		show_panel = show ? true : false;
	}

	this.start = function () {
		setInterval(loop, 1);
		registerLoop(500, function () {
			last_hpp = Communication.getGame().hero.getHpPercent();
			return true;
		});
		registerLoop(100, function () {
			for (var t in move_dir) {
				if (walkDir[t]) {
					Communication.move[move_dir[t]]();
					return true;
				}
			}
			return false;
		});
		Render.add(hud);

	}

})();