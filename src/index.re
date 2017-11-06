let canvas = Canvas.getCanvasById("canvas");

let canvasParent = Canvas.parentNode(canvas);

Canvas.setWidth(canvas, Canvas.clientWidth(canvasParent));

Canvas.setHeight(canvas, Canvas.clientHeight(canvasParent));

let context = Canvas.getContext(canvas, `twoD);

let width = float_of_int @@ Canvas.getWidth(canvas);

let height = float_of_int @@ Canvas.getHeight(canvas);

let center = (width /. 2., height /. 2.);

let gravity = Vector2.mul(Vector2.down, 0.01);

type state = list(Particle.t);

let state: ref(state) = ref([]);

type msg =
  | Tick
  | SpawnParticle(Vector2.t, Vector2.t);

let update = (msg, state) : state =>
  switch msg {
  | Tick => List.map(Particle.update(gravity), state)
  | SpawnParticle(pos, vel) =>
    let colour = (Random.int(256), Random.int(256), Random.int(256));
    [Particle.make(pos, vel, colour), ...state]
  };

let draw = (state) => {
  Canvas.clearCanvas(canvas, context);
  List.iter(Particle.draw(context), state)
};

let dispatch = (msg) => {
  let newState = update(msg, state^);
  state := newState;
  draw(state^)
};

[@bs.val] external setInterval : (unit => unit, int) => unit = "setInterval";

setInterval(() => dispatch(Tick), 10);

setInterval(() => dispatch(SpawnParticle(center, Vector2.randomUnit())), 10);
