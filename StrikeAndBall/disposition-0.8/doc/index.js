function add_random_lines(txtelem) {
	chars = "abcdefghijklmnopqrstuvwxyz"
	for (i = 0; i < 40; i++) {
		line = ""
		for (j = 0; j < 80; j++)
			line += chars.charAt(Math.floor(Math.random()
							* chars.length))
		txtelem.appendChild(document.createTextNode(line))
		txtelem.appendChild(document.createElement("br"))
	}
}

