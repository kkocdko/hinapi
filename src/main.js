const hinapi = require("../build/hinapi.node");
console.log("calc 1 + 2 =", hinapi.calcAdd(1, 2));
console.log("created object =", hinapi.createObject("tom", 12));
hinapi.runCallback((arg) => {
  console.log(`callback argument =`, arg);
});
(async () => {
  let v = await hinapi.hiPromise();
  console.log("promise resolved value =", v);
})();
