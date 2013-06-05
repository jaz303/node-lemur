const PPQN              = 96;
const TEMPO             = 140;
const PREFILL_TRIGGER   = 300;
const PREFILL_BEATS     = 1;

function t(bar, beat, pulse) {
  pulse = pulse || 0;
  return (((bar * 4) + beat) * PPQN) + (pulse < 1 ? Math.floor(pulse * PPQN) : pulse);
}

function toMillis(timestamp) {
  var msPerPulse = (60 / (TEMPO * PPQN)) * 1000;
  return (timestamp * msPerPulse) | 0;
}

var loops = [];

function fill(currentTime, duration) {
  
  console.log("beat: " + Math.floor(currentTime / PPQN), "abspulse: " + currentTime);
  
  loops.forEach(function(loop) {
    
    if (loop.muted)
      return;
      
    var loopFn    = loop.fn,
        loopStart = Math.floor(currentTime / loopFn.duration) * loopFn.duration,
        fillEnd   = currentTime + duration;
    
    while (loopStart < fillEnd) {
      // TODO: loopFn should perhaps also receive time window that we're requesting it
      // to calculate - would improve performance, particularly for any loops that
      // do intensive calculations
      var loopEvents = loopFn(loopStart);
      // TODO: iterate over loopEvents and deliver only
      // those we're interested in to the playback engine.
      loopStart += loopFn.duration;
    }
    
  });
}

function start() {
  
  var musicalNow    = 0,
      startTime     = Date.now(),
      deadline      = Math.Infinity;
      
  function tick() {
    var pp  = PREFILL_BEATS * PPQN,
        now = Date.now();
        
    if (now > deadline) {
      console.log("deadline missed, playback will suffer :(");
    }
    
    // fill based on the current musical time
    fill(musicalNow, pp);
    
    // update music time
    musicalNow += pp;
    
    // deadline is the wallclock time by which buffer must have been filed
    deadline = startTime + toMillis(musicalNow);
    
    // target is time at which we want to next fill the buffer
    var target = deadline - PREFILL_TRIGGER;
        
    if (now >= target) {
      console.log("underrun!");
      setTimeout(tick, 0);
    } else {
      setTimeout(tick, target - now);
    }
  }
      
  tick();
  
}

function play(loopFn) {
  loops[loops.length] = {
    fn          : loopFn,
    muted       : false
  };
}

function createLoop(duration, fn) {
  fn.duration = duration;
  return fn;
}

var loop1 = createLoop(t(4, 0, 0), function(o) {
  console.log("4, 1", o);
});

var loop2 = createLoop(t(4, 0, 0), function(o) {
  console.log("4, 2", o);
});

var loop3 = createLoop(t(2, 0, 0), function(o) {
  console.log("2, 1", o);
});

var loop4 = createLoop(t(3, 0, 0), function(o) {
  console.log("3, 1", o);
});

play(loop1);
play(loop2);
play(loop3);
play(loop4);

start();