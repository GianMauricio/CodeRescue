//setup variables
var scene, camera, renderer, camControls;
var planetSides = 48;

//containers for objects
var sun;
	var halo;

var mercury;
	var mercuryOrbit;

var venus;
	var venusOrbit;

var earth;
	var earthMoon;
		var earthMoonOrbit;
	var earthOrbit;

var mars;
	var marsOrbit;

var jupiter;
	var jupiterOrbit;

var saturn;
	var ringSaturn1;
	var ringSaturn2;
	var ringSaturn3;
	var saturnOrbit;

var neptune;
	var neptuneOrbit;

var uranus;
	var ringUranus1;
	var ringUranus2;
	var uranusOrbit;

var pluto;
	var plutoOrbit;

//utility functions for object making, OOP abstraction in action
var earthData = makePlanet(365.0, 0.015, 25, "earth", "Assets/earth.jpg", 1, planetSides);
var moonData = makePlanet(29.0, 0.01, 2.8, "moon", "Assets/moon.jpg", 0.5, planetSides);
var orbitData = {value: 200, followTrack: true, Rotate: true};

//timer literally yoinked from tutorial
var clock = new THREE.Clock();

//allows for easy planet creation
function makePlanet(OrbitRate, RotateRate, startPos, Name, Texture, Size, Sides){
	//thank god this still works, yoinked from Node.js
	return {
		orbitRate: OrbitRate,
		rotationRate: RotateRate,
		currPos: startPos,
		name: Name,
		texture: Texture,
		size: Size,
		sides: Sides
	};
}

//creates horizontal ring
function makeRingH(size, Diameter, facets, Color, Name, position){
	var ringGeometry = new THREE.RingGeometry(size, Diameter, facets);
	var ringMaterial = new THREE.MeshBasicMaterial({color: Color, side: THREE.DoubleSide});
	var newRing = new THREE.Mesh(ringGeometry, ringMaterial);
	newRing.name = Name;
	newRing.position.set(position, 0, 0);
	newRing.rotation.x = Math.PI / 2; /*Spin sideways*/
	scene.add(newRing);
	return newRing;
}

//creates vertical ring
function makeRingV(size, Diameter, facets, Color, Name, position){
	var ringGeometry = new THREE.RingGeometry(size, Diameter, facets);
	var ringMaterial = new THREE.MeshBasicMaterial({color: Color, side: THREE.DoubleSide});
	var newRing = new THREE.Mesh(ringGeometry, ringMaterial);
	newRing.name = Name;
	newRing.position.set(position, 0, 0);
	newRing.rotation.y = Math.PI / 2; /*Spin vertically*/
	scene.add(newRing);

	return newRing;
}

//creates materials
function makeMaterial(type, color, Texture){
	//yoinked from tutorial because I didn't know how to use a ternary operator XD
	var MaterialOptions = {
		color: color === undefined ?  'rgb(255, 255, 255)' : color,
		map: Texture === undefined ? null : Texture
	};

	switch(type){
		case 'simple':
			return new THREE.MeshBasicMaterial(MaterialOptions);
			break;
		case 'lambert':
			return new THREE.MeshLambertMaterial(MaterialOptions);
			break;
		case 'phong':
			return new THREE.MeshPhongMaterial(MaterialOptions);
			break;
		case 'standard':
			return new THREE.MeshStandardMaterial(MaterialOptions);
			break;

		//stuff keeps breaking during debug, therefore this is needed	
		default:
			return new THREE.MeshBasicMaterial(MaterialOptions);
			break;
	}
}

//creates spheres 
function makeSphere(material, size, sides){
	var geometry = new THREE.SphereGeometry(size, sides, sides);
	var body = new THREE.Mesh(geometry, material);
	body.castShadow = true; /*Tutorial taught me this*/

	return body;
}

//creates actual orbits, took the longest to make since I am astronomy noob
function pathOrbits(){
	var pathWidth = 0.01;
	mercuryOrbit = ;
	venusOrbit = ;
	earthOrbit = makeRingH(earthData.currPos + pathWidth, earthData.currPos - pathWidth, 320, 0xffffff, "earthOrbit", 0);
		earthMoonOrbit = ;
	marsOrbit = ;
	jupiterOrbit = ;
	saturnOrbit = ;
	neptune = ;
	uranus = ;
	pluto = ;
}

//adds the planet to scene, remade from tutorial function to fit new format
function spawnPlanet(planetData, xPos, yPos, zPos, Material){
	var material;
	var loadTexture;
	var planet;

	//yoinked from tutorial
	//not sure why the if statements are needed, I assume it's Three.js specialized
	if(planetData.texture && planetData.texture !== ""){
		loadTexture = new THREE.ImageUtils.loadTexture(planetData.texture);
	}

	if(Material){
		material = makeMaterial(Material, "rgb(255, 255, 255 )", loadTexture);
	}

	else{
		material = makeMaterial("lambert", "rgb(255, 255, 255 )", loadTexture);
	}

	material.receiveShadow = true;
	material.castShadow = true;

	planet = makeSphere(material, planetData.size, planetData.sides);
	planet.receiveShadow = true; /*I think this is redundant, but it breaks if I delete it*/
	planet.name = planetData.name;
	scene.add(planet);
	planet.position.set(xPos, yPos, zPos);

	return planet;
}

//also yoinked from tutorial because I had no idea how to even start this
function makeLight(strength, color){
	var light = new THREE.PointLight(color, strength);
	light.castShadow = true;

	light.shadow.bias = 0.001;
	light.shadow.mapSize.width = 2048;
	light.shadow.mapSize.height = 2048;

	return light;
}

//Big brain time
function movePlanet(planet, data, Time, stopRotate){/*clock better work*/
	//faclitate rotation of planet
	if(orbitData.Rotate && !stopRotate){
		planet.rotation.y += data.rotationRate;
	}

	//facilitate revolution of planet
	if(orbitData.followTrack){
		planet.position.x = Math.cos(Time * (1.0 / (data.orbitRate * orbitData.value)) + 10.0) * data.currPos;
		planet.position.z = Math.sin(Time * (1.0 / (data.orbitRate * orbitData.value)) + 10.0) * data.currPos;
	}
}

//Tutorial helped a lot with this one
function moveSatellite(moon, planet, data, Time){
	movePlanet(moon, data, Time);
	if(orbitData.followTrack){
		moon.position.x = moon.position.x + planet.position.x;
		moon.position.z = moon.position.z + planet.position.z;
	}
}

//actual code
function update(renderer, scene, camera, controls){
	halo.position.copy(sun.position);
	controls.update();

	var time = Date.now();

	movePlanet(earth, earthData, time);
	movePlanet(ring, earthData, time, true);
	moveSatellite(moon, earth, moonData, time);

	//yoinked from tutorial :3 because recursion is weird in js
	renderer.render(scene, camera);
	requestAnimationFrame(function () {
		update(renderer, scene, camera, controls)
	});
}

//shamelessly yoinked from tutorial
function init(){
	//make camera
	camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 1, 1000);
	camera.position.x = -30;
	camera.position.y = 30;
	camera.position.z = 30;

	camera.lookAt(new THREE.Vector3(0,0,0));

	//make scene
	scene = new THREE.Scene();

	//make renderer
	renderer = new THREE.WebGLRenderer();
	renderer.setSize(window.innerWidth, window.innerHeight);

	//@ the renderer to the div section
	document.getElementById('webgl').appendChild(renderer.domElement);

	//create control system for camera
	
}