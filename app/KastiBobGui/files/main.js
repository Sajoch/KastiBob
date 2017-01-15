window.addEventListener("resize", onresize);
var loadWindow = false;
window.addEventListener("load", function () {
	loadWindow = true;
});

function start() {
	if (loadWindow) {
		onload();
	} else {
		window.addEventListener("load", onload);
	}
}

function reload() {
	window.location.reload();
}

function onload() {
	var need_files = ["hero.js", "communication.js",
		"img.js", "render.js", "console.js",
		"keys.js", "ui.js", "map.js"
	];
	var $loading = $("<div>").addClass("loading").appendTo("body");
	var $log = $("<div>").appendTo($loading);
	var files = need_files.length - 1;
	var loading_files = 0;
	var loaded_files = 0;

	function log(txt) {
		var $msg = $("<div>").text(txt).appendTo($log);
		return $msg;
	}

	function seqLoad() {
		if (loaded_files < files) {
			startLoading(need_files[loaded_files], seqLoad);
		} else {
			startLoading(need_files[loaded_files], after_loading);
		}
	}

	function startLoading(path, cb) {
		loading_files++;
		var el = log("Loading " + path + "...");
		$.ajax({
			type: "GET",
			url: "qrc:\\" + path,
			dataType: "script",
			error: function (xhr, e, err) {
				el.text(el.text() + "failed (" + err.toString() + ")");
			},
			success: function () {
				loaded_files++;
				loading_files--;
				el.text(el.text() + "done");
				cb();
			}
		});
	}

	function after_loading() {
		if (loading_files == 0 && loaded_files == need_files.length) {
			$head_el.text($head_el.text() + "done");
			log("Starting...");
			start_wm();
		}
	}

	function start_wm() {
		try {
			Communication.start();
			Render.start();
			map.start(Communication);
			onresize();
			$loading.remove();
			Keys.registerHotkey(87, ui.moveUp, "normal");
			Keys.registerHotkey(65, ui.moveLeft, "normal");
			Keys.registerHotkey(68, ui.moveRight, "normal");
			Keys.registerHotkey(83, ui.moveDown, "normal");
			ui.start();
		} catch (e) {
			Console.error(e);
		}
	}
	var $head_el = log("Loading files...");
	seqLoad();
}

function onresize() {
	var h = window.innerHeight;
	var w = window.innerWidth;
	if (typeof Render != "undefined") {
		Render.resize(w, h);
	}
	//document.body.style.width=w+"px";
	//document.body.style.height=h+"px";
}