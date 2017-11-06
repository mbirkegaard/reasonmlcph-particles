type t = {
    position: Vector2.t,
    velocity: Vector2.t,
    colour: (int, int, int)
};

let make position velocity colour => {
    { position, velocity, colour };
};

let draw context { position, colour } => {
    Canvas.drawCircle context colour::colour center::position 2.0;
};

let update acceleration particle => {
    let { position, velocity } = particle;
    let newVelocity = Vector2.add velocity acceleration; 
    {...particle, position: Vector2.add position newVelocity, velocity: newVelocity }
};