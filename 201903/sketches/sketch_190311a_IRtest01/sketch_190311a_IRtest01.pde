class Sensor {
  float x, y;
  int levelNum = 10;
  int gap = 50;

  Sensor(float x, float y) {
    this.x = x;
    this.y = y;
  }

  void setup() {
    for (int i = 0; i<levelNum; i++) {
      circles.add(new RangeCircle(x, y, (i+1)*gap));
    }
  }
}

class RangeCircle {
  float x, y, r;
  Boolean changeColorflg = false;

  RangeCircle(float x, float y, float r) {
    this.x = x;
    this.y = y;
    this.r = r;
  }

  void update(float ms_x, float ms_y) {
    changeColorflg = checkMouseover(ms_x, ms_y);  // update flg based on mouseover
  }

  Boolean checkMouseover(float ms_x, float ms_y) {
    Boolean res = false;

    float min_dist = r;

    float dist = (new PVector(ms_x, ms_y), new PVector(x, y));

    if (dist < min_dist) {
      res = true;
    }

    return res;
  }

  void draw() {
    pushMatrix();
    translate(x, y);

    stroke(0);
    if (changeColorflg) {
      // need mask
      fill(0, 0, 255);
    } else {
      noFill();
    }

    circle(0, 0, r);
    popMatrix();
  }
}


ArrayList<Sensor> sensors  = new ArrayList<Sensor>();
ArrayList<RangeCircle> circles  = new ArrayList<RangeCircle>();

void setup() {
  size(1200, 700);

  sensors.add(new Sensor(width*2/5, height/2));
  sensors.add(new Sensor(width*3/5, height/2));
  for (Sensor s : sensors) {
    s.setup();
  }
}

void draw() {
  background(255);
  for (RangeCircle c : circles) {
    c.update(mouseX, mouseY);
    c.draw();
  }
}
