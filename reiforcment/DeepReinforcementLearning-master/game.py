import numpy as np
import logging

from collections import deque

class Game:

	def __init__(self):
		self.currentPlayer = 1
		#cria o array para o tabuleiro e diz que o player a jogar e o 1 (black)
		self.gameState = GameState(np.array([
		0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0,
		 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1,
		 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0,
		 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0,
		 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0,
		 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0,
		 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1,
		 -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0,
		 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0,
		 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0,
		 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1,
		 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0,
		 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0], dtype=np.int), 1)
		self.actionSpace = np.zeros(14*14, dtype=np.int)
		self.pieces = {'1':'B', '0': '-', '-1':'W'}
		self.grid_shape = (14,14)
		self.input_shape = (2,14,14)
		self.name = 'Wirlwind'
		self.state_size = len(self.gameState.binary)
		self.action_size = len(self.actionSpace)

	def reset(self):
		self.gameState = GameState(np.array([
		0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1,
		-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
		0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0], dtype=np.int), 1)
		self.currentPlayer = 1
		return self.gameState

	def step(self, action):
		next_state, value, done = self.gameState.takeAction(action)
		self.gameState = next_state
		self.currentPlayer = -self.currentPlayer
		info = None
		return ((next_state, value, done, info))

	def identities(self, state, actionValues):
		identities = [(state,actionValues)]

		currentBoard = state.board
		currentAV = actionValues
		
		#invertido no eixo dos y
		currentBoard = np.array([
			currentBoard[13], currentBoard[12], currentBoard[11], currentBoard[10], currentBoard[9], currentBoard[8], currentBoard[7], currentBoard[6], currentBoard[5], currentBoard[4], currentBoard[3], currentBoard[2], currentBoard[1], currentBoard[0],
			currentBoard[27], currentBoard[26], currentBoard[25], currentBoard[24], currentBoard[23], currentBoard[22], currentBoard[21], currentBoard[20], currentBoard[19], currentBoard[18], currentBoard[17], currentBoard[16], currentBoard[15], currentBoard[14],
			currentBoard[41], currentBoard[40], currentBoard[39], currentBoard[38], currentBoard[37], currentBoard[36], currentBoard[35], currentBoard[34], currentBoard[33], currentBoard[32], currentBoard[31], currentBoard[30], currentBoard[29], currentBoard[28],
			currentBoard[55], currentBoard[54], currentBoard[53], currentBoard[52], currentBoard[51], currentBoard[50], currentBoard[49], currentBoard[48], currentBoard[47], currentBoard[46], currentBoard[45], currentBoard[44], currentBoard[43], currentBoard[42],
			currentBoard[69], currentBoard[68], currentBoard[67], currentBoard[66], currentBoard[65], currentBoard[64], currentBoard[63], currentBoard[62], currentBoard[61], currentBoard[60], currentBoard[59], currentBoard[58], currentBoard[57], currentBoard[56],
			currentBoard[83], currentBoard[82], currentBoard[81], currentBoard[80], currentBoard[79], currentBoard[78], currentBoard[77], currentBoard[76], currentBoard[75], currentBoard[74], currentBoard[73], currentBoard[72], currentBoard[71], currentBoard[70],
			currentBoard[97], currentBoard[96], currentBoard[95], currentBoard[94], currentBoard[93], currentBoard[92], currentBoard[91], currentBoard[90], currentBoard[89], currentBoard[88], currentBoard[87], currentBoard[86], currentBoard[85], currentBoard[84],
			currentBoard[111], currentBoard[110], currentBoard[109], currentBoard[108], currentBoard[107], currentBoard[106], currentBoard[105], currentBoard[104], currentBoard[103], currentBoard[102], currentBoard[101], currentBoard[100], currentBoard[99], currentBoard[98],
			currentBoard[125], currentBoard[124], currentBoard[123], currentBoard[122], currentBoard[121], currentBoard[120], currentBoard[119], currentBoard[118], currentBoard[117], currentBoard[116], currentBoard[115], currentBoard[114], currentBoard[113], currentBoard[112],
			currentBoard[139], currentBoard[138], currentBoard[137], currentBoard[136], currentBoard[135], currentBoard[134], currentBoard[133], currentBoard[132], currentBoard[131], currentBoard[130], currentBoard[129], currentBoard[128], currentBoard[127], currentBoard[126],
			currentBoard[153], currentBoard[152], currentBoard[151], currentBoard[150], currentBoard[149], currentBoard[148], currentBoard[147], currentBoard[146], currentBoard[145], currentBoard[144], currentBoard[143], currentBoard[142], currentBoard[141], currentBoard[140],
			currentBoard[167], currentBoard[166], currentBoard[165], currentBoard[164], currentBoard[163], currentBoard[162], currentBoard[161], currentBoard[160], currentBoard[159], currentBoard[158], currentBoard[157], currentBoard[156], currentBoard[155], currentBoard[154],
			currentBoard[181], currentBoard[180], currentBoard[179], currentBoard[178], currentBoard[177], currentBoard[176], currentBoard[175], currentBoard[174], currentBoard[173], currentBoard[172], currentBoard[171], currentBoard[170], currentBoard[169], currentBoard[168],
			currentBoard[195], currentBoard[194], currentBoard[193], currentBoard[192], currentBoard[191], currentBoard[190], currentBoard[189], currentBoard[188], currentBoard[187], currentBoard[186], currentBoard[185], currentBoard[184], currentBoard[183], currentBoard[182]
				])

		currentAV = np.array([
			currentAV[13], currentAV[12], currentAV[11], currentAV[10], currentAV[9], currentAV[8], currentAV[7], currentAV[6], currentAV[5], currentAV[4], currentAV[3], currentAV[2], currentAV[1], currentAV[0],
			currentAV[27], currentAV[26], currentAV[25], currentAV[24], currentAV[23], currentAV[22], currentAV[21], currentAV[20], currentAV[19], currentAV[18], currentAV[17], currentAV[16], currentAV[15], currentAV[14],
			currentAV[41], currentAV[40], currentAV[39], currentAV[38], currentAV[37], currentAV[36], currentAV[35], currentAV[34], currentAV[33], currentAV[32], currentAV[31], currentAV[30], currentAV[29], currentAV[28],
			currentAV[55], currentAV[54], currentAV[53], currentAV[52], currentAV[51], currentAV[50], currentAV[49], currentAV[48], currentAV[47], currentAV[46], currentAV[45], currentAV[44], currentAV[43], currentAV[42],
			currentAV[69], currentAV[68], currentAV[67], currentAV[66], currentAV[65], currentAV[64], currentAV[63], currentAV[62], currentAV[61], currentAV[60], currentAV[59], currentAV[58], currentAV[57], currentAV[56],
			currentAV[83], currentAV[82], currentAV[81], currentAV[80], currentAV[79], currentAV[78], currentAV[77], currentAV[76], currentAV[75], currentAV[74], currentAV[73], currentAV[72], currentAV[71], currentAV[70],
			currentAV[97], currentAV[96], currentAV[95], currentAV[94], currentAV[93], currentAV[92], currentAV[91], currentAV[90], currentAV[89], currentAV[88], currentAV[87], currentAV[86], currentAV[85], currentAV[84],
			currentAV[111], currentAV[110], currentAV[109], currentAV[108], currentAV[107], currentAV[106], currentAV[105], currentAV[104], currentAV[103], currentAV[102], currentAV[101], currentAV[100], currentAV[99], currentAV[98],
			currentAV[125], currentAV[124], currentAV[123], currentAV[122], currentAV[121], currentAV[120], currentAV[119], currentAV[118], currentAV[117], currentAV[116], currentAV[115], currentAV[114], currentAV[113], currentAV[112],
			currentAV[139], currentAV[138], currentAV[137], currentAV[136], currentAV[135], currentAV[134], currentAV[133], currentAV[132], currentAV[131], currentAV[130], currentAV[129], currentAV[128], currentAV[127], currentAV[126],
			currentAV[153], currentAV[152], currentAV[151], currentAV[150], currentAV[149], currentAV[148], currentAV[147], currentAV[146], currentAV[145], currentAV[144], currentAV[143], currentAV[142], currentAV[141], currentAV[140],
			currentAV[167], currentAV[166], currentAV[165], currentAV[164], currentAV[163], currentAV[162], currentAV[161], currentAV[160], currentAV[159], currentAV[158], currentAV[157], currentAV[156], currentAV[155], currentAV[154],
			currentAV[181], currentAV[180], currentAV[179], currentAV[178], currentAV[177], currentAV[176], currentAV[175], currentAV[174], currentAV[173], currentAV[172], currentAV[171], currentAV[170], currentAV[169], currentAV[168],
			currentAV[195], currentAV[194], currentAV[193], currentAV[192], currentAV[191], currentAV[190], currentAV[189], currentAV[188], currentAV[187], currentAV[186], currentAV[185], currentAV[184], currentAV[183], currentAV[182]
				])

		identities.append((GameState(currentBoard, state.playerTurn), currentAV))

		#inverrtido no eixo dos x
		currentBoard = np.array([
			currentBoard[182], currentBoard[183], currentBoard[184], currentBoard[185], currentBoard[186], currentBoard[187], currentBoard[188], currentBoard[189], currentBoard[190], currentBoard[191], currentBoard[192], currentBoard[193], currentBoard[194], currentBoard[195],
			currentBoard[168], currentBoard[169], currentBoard[170], currentBoard[171], currentBoard[172], currentBoard[173], currentBoard[174], currentBoard[175], currentBoard[176], currentBoard[177], currentBoard[178], currentBoard[179], currentBoard[180], currentBoard[181],
			currentBoard[154], currentBoard[155], currentBoard[156], currentBoard[157], currentBoard[158], currentBoard[159], currentBoard[160], currentBoard[161], currentBoard[162], currentBoard[163], currentBoard[164], currentBoard[165], currentBoard[166], currentBoard[167],
			currentBoard[140], currentBoard[141], currentBoard[142], currentBoard[143], currentBoard[144], currentBoard[145], currentBoard[146], currentBoard[147], currentBoard[148], currentBoard[149], currentBoard[150], currentBoard[151], currentBoard[152], currentBoard[153],
			currentBoard[126], currentBoard[127], currentBoard[128], currentBoard[129], currentBoard[130], currentBoard[131], currentBoard[132], currentBoard[133], currentBoard[134], currentBoard[135], currentBoard[136], currentBoard[137], currentBoard[138], currentBoard[139],
			currentBoard[112], currentBoard[113], currentBoard[114], currentBoard[115], currentBoard[116], currentBoard[117], currentBoard[118], currentBoard[119], currentBoard[120], currentBoard[121], currentBoard[122], currentBoard[123], currentBoard[124], currentBoard[125],
			currentBoard[98], currentBoard[99], currentBoard[100], currentBoard[101], currentBoard[102], currentBoard[103], currentBoard[104], currentBoard[105], currentBoard[106], currentBoard[107], currentBoard[108], currentBoard[109], currentBoard[110], currentBoard[111],
			currentBoard[84], currentBoard[85], currentBoard[86], currentBoard[87], currentBoard[88], currentBoard[89], currentBoard[90], currentBoard[91], currentBoard[92], currentBoard[93], currentBoard[94], currentBoard[95], currentBoard[96], currentBoard[97],
			currentBoard[70], currentBoard[71], currentBoard[72], currentBoard[73], currentBoard[74], currentBoard[75], currentBoard[76], currentBoard[77], currentBoard[78], currentBoard[79], currentBoard[80], currentBoard[81], currentBoard[82], currentBoard[83],
			currentBoard[56], currentBoard[57], currentBoard[58], currentBoard[59], currentBoard[60], currentBoard[61], currentBoard[62], currentBoard[63], currentBoard[64], currentBoard[65], currentBoard[66], currentBoard[67], currentBoard[68], currentBoard[69],
			currentBoard[42], currentBoard[43], currentBoard[44], currentBoard[45], currentBoard[46], currentBoard[47], currentBoard[48], currentBoard[49], currentBoard[50], currentBoard[51], currentBoard[52], currentBoard[53], currentBoard[54], currentBoard[55],
			currentBoard[28], currentBoard[29], currentBoard[30], currentBoard[31], currentBoard[32], currentBoard[33], currentBoard[34], currentBoard[35], currentBoard[36], currentBoard[37], currentBoard[38], currentBoard[39], currentBoard[40], currentBoard[41],
			currentBoard[14], currentBoard[15], currentBoard[16], currentBoard[17], currentBoard[18], currentBoard[19], currentBoard[20], currentBoard[21], currentBoard[22], currentBoard[23], currentBoard[24], currentBoard[25], currentBoard[26], currentBoard[27],
			currentBoard[0], currentBoard[1], currentBoard[2], currentBoard[3], currentBoard[4], currentBoard[5], currentBoard[6], currentBoard[7], currentBoard[8], currentBoard[9], currentBoard[10], currentBoard[11], currentBoard[12], currentBoard[13]
				])

		currentAV = np.array([
			currentAV[182], currentAV[183], currentAV[184], currentAV[185], currentAV[186], currentAV[187], currentAV[188], currentAV[189], currentAV[190], currentAV[191], currentAV[192], currentAV[193], currentAV[194], currentAV[195],
			currentAV[168], currentAV[169], currentAV[170], currentAV[171], currentAV[172], currentAV[173], currentAV[174], currentAV[175], currentAV[176], currentAV[177], currentAV[178], currentAV[179], currentAV[180], currentAV[181],
			currentAV[154], currentAV[155], currentAV[156], currentAV[157], currentAV[158], currentAV[159], currentAV[160], currentAV[161], currentAV[162], currentAV[163], currentAV[164], currentAV[165], currentAV[166], currentAV[167],
			currentAV[140], currentAV[141], currentAV[142], currentAV[143], currentAV[144], currentAV[145], currentAV[146], currentAV[147], currentAV[148], currentAV[149], currentAV[150], currentAV[151], currentAV[152], currentAV[153],
			currentAV[126], currentAV[127], currentAV[128], currentAV[129], currentAV[130], currentAV[131], currentAV[132], currentAV[133], currentAV[134], currentAV[135], currentAV[136], currentAV[137], currentAV[138], currentAV[139],
			currentAV[112], currentAV[113], currentAV[114], currentAV[115], currentAV[116], currentAV[117], currentAV[118], currentAV[119], currentAV[120], currentAV[121], currentAV[122], currentAV[123], currentAV[124], currentAV[125],
			currentAV[98], currentAV[99], currentAV[100], currentAV[101], currentAV[102], currentAV[103], currentAV[104], currentAV[105], currentAV[106], currentAV[107], currentAV[108], currentAV[109], currentAV[110], currentAV[111],
			currentAV[84], currentAV[85], currentAV[86], currentAV[87], currentAV[88], currentAV[89], currentAV[90], currentAV[91], currentAV[92], currentAV[93], currentAV[94], currentAV[95], currentAV[96], currentAV[97],
			currentAV[70], currentAV[71], currentAV[72], currentAV[73], currentAV[74], currentAV[75], currentAV[76], currentAV[77], currentAV[78], currentAV[79], currentAV[80], currentAV[81], currentAV[82], currentAV[83],
			currentAV[56], currentAV[57], currentAV[58], currentAV[59], currentAV[60], currentAV[61], currentAV[62], currentAV[63], currentAV[64], currentAV[65], currentAV[66], currentAV[67], currentAV[68], currentAV[69],
			currentAV[42], currentAV[43], currentAV[44], currentAV[45], currentAV[46], currentAV[47], currentAV[48], currentAV[49], currentAV[50], currentAV[51], currentAV[52], currentAV[53], currentAV[54], currentAV[55],
			currentAV[28], currentAV[29], currentAV[30], currentAV[31], currentAV[32], currentAV[33], currentAV[34], currentAV[35], currentAV[36], currentAV[37], currentAV[38], currentAV[39], currentAV[40], currentAV[41],
			currentAV[14], currentAV[15], currentAV[16], currentAV[17], currentAV[18], currentAV[19], currentAV[20], currentAV[21], currentAV[22], currentAV[23], currentAV[24], currentAV[25], currentAV[26], currentAV[27],
			currentAV[0], currentAV[1], currentAV[2], currentAV[3], currentAV[4], currentAV[5], currentAV[6], currentAV[7], currentAV[8], currentAV[9], currentAV[10], currentAV[11], currentAV[12], currentAV[13]
				])

		identities.append((GameState(currentBoard, state.playerTurn), currentAV))


		#inverrtido no eixo dos x e dos y
		currentBoard = np.array([
			currentBoard[195], currentBoard[194], currentBoard[193], currentBoard[192], currentBoard[191], currentBoard[190], currentBoard[189], currentBoard[188], currentBoard[187], currentBoard[186], currentBoard[185], currentBoard[184], currentBoard[183], currentBoard[182],
			currentBoard[181], currentBoard[180], currentBoard[179], currentBoard[178], currentBoard[177], currentBoard[176], currentBoard[175], currentBoard[174], currentBoard[173], currentBoard[172], currentBoard[171], currentBoard[170], currentBoard[169], currentBoard[168],
			currentBoard[167], currentBoard[166], currentBoard[165], currentBoard[164], currentBoard[163], currentBoard[162], currentBoard[161], currentBoard[160], currentBoard[159], currentBoard[158], currentBoard[157], currentBoard[156], currentBoard[155], currentBoard[154],
			currentBoard[153], currentBoard[152], currentBoard[151], currentBoard[150], currentBoard[149], currentBoard[148], currentBoard[147], currentBoard[146], currentBoard[145], currentBoard[144], currentBoard[143], currentBoard[142], currentBoard[141], currentBoard[140],
			currentBoard[139], currentBoard[138], currentBoard[137], currentBoard[136], currentBoard[135], currentBoard[134], currentBoard[133], currentBoard[132], currentBoard[131], currentBoard[130], currentBoard[129], currentBoard[128], currentBoard[127], currentBoard[126],
			currentBoard[125], currentBoard[124], currentBoard[123], currentBoard[122], currentBoard[121], currentBoard[120], currentBoard[119], currentBoard[118], currentBoard[117], currentBoard[116], currentBoard[115], currentBoard[114], currentBoard[113], currentBoard[112],
			currentBoard[111], currentBoard[110], currentBoard[109], currentBoard[108], currentBoard[107], currentBoard[106], currentBoard[105], currentBoard[104], currentBoard[103], currentBoard[102], currentBoard[101], currentBoard[100], currentBoard[99], currentBoard[98],
			currentBoard[97], currentBoard[96], currentBoard[95], currentBoard[94], currentBoard[93], currentBoard[92], currentBoard[91], currentBoard[90], currentBoard[89], currentBoard[88], currentBoard[87], currentBoard[86], currentBoard[85], currentBoard[84],
			currentBoard[83], currentBoard[82], currentBoard[81], currentBoard[80], currentBoard[79], currentBoard[78], currentBoard[77], currentBoard[76], currentBoard[75], currentBoard[74], currentBoard[73], currentBoard[72], currentBoard[71], currentBoard[70],
			currentBoard[69], currentBoard[68], currentBoard[67], currentBoard[66], currentBoard[65], currentBoard[64], currentBoard[63], currentBoard[62], currentBoard[61], currentBoard[60], currentBoard[59], currentBoard[58], currentBoard[57], currentBoard[56],
			currentBoard[55], currentBoard[54], currentBoard[53], currentBoard[52], currentBoard[51], currentBoard[50], currentBoard[49], currentBoard[48], currentBoard[47], currentBoard[46], currentBoard[45], currentBoard[44], currentBoard[43], currentBoard[42],
			currentBoard[41], currentBoard[40], currentBoard[39], currentBoard[38], currentBoard[37], currentBoard[36], currentBoard[35], currentBoard[34], currentBoard[33], currentBoard[32], currentBoard[31], currentBoard[30], currentBoard[29], currentBoard[28],
			currentBoard[27], currentBoard[26], currentBoard[25], currentBoard[24], currentBoard[23], currentBoard[22], currentBoard[21], currentBoard[20], currentBoard[19], currentBoard[18], currentBoard[17], currentBoard[16], currentBoard[15], currentBoard[14],
			currentBoard[13], currentBoard[12], currentBoard[11], currentBoard[10], currentBoard[9], currentBoard[8], currentBoard[7], currentBoard[6], currentBoard[5], currentBoard[4], currentBoard[3], currentBoard[2], currentBoard[1], currentBoard[0]
				])

		currentAV = np.array([
			currentAV[195], currentAV[194], currentAV[193], currentAV[192], currentAV[191], currentAV[190], currentAV[189], currentAV[188], currentAV[187], currentAV[186], currentAV[185], currentAV[184], currentAV[183], currentAV[182],
			currentAV[181], currentAV[180], currentAV[179], currentAV[178], currentAV[177], currentAV[176], currentAV[175], currentAV[174], currentAV[173], currentAV[172], currentAV[171], currentAV[170], currentAV[169], currentAV[168],
			currentAV[167], currentAV[166], currentAV[165], currentAV[164], currentAV[163], currentAV[162], currentAV[161], currentAV[160], currentAV[159], currentAV[158], currentAV[157], currentAV[156], currentAV[155], currentAV[154],
			currentAV[153], currentAV[152], currentAV[151], currentAV[150], currentAV[149], currentAV[148], currentAV[147], currentAV[146], currentAV[145], currentAV[144], currentAV[143], currentAV[142], currentAV[141], currentAV[140],
			currentAV[139], currentAV[138], currentAV[137], currentAV[136], currentAV[135], currentAV[134], currentAV[133], currentAV[132], currentAV[131], currentAV[130], currentAV[129], currentAV[128], currentAV[127], currentAV[126],
			currentAV[125], currentAV[124], currentAV[123], currentAV[122], currentAV[121], currentAV[120], currentAV[119], currentAV[118], currentAV[117], currentAV[116], currentAV[115], currentAV[114], currentAV[113], currentAV[112],
			currentAV[111], currentAV[110], currentAV[109], currentAV[108], currentAV[107], currentAV[106], currentAV[105], currentAV[104], currentAV[103], currentAV[102], currentAV[101], currentAV[100], currentAV[99], currentAV[98],
			currentAV[97], currentAV[96], currentAV[95], currentAV[94], currentAV[93], currentAV[92], currentAV[91], currentAV[90], currentAV[89], currentAV[88], currentAV[87], currentAV[86], currentAV[85], currentAV[84],
			currentAV[83], currentAV[82], currentAV[81], currentAV[80], currentAV[79], currentAV[78], currentAV[77], currentAV[76], currentAV[75], currentAV[74], currentAV[73], currentAV[72], currentAV[71], currentAV[70],
			currentAV[69], currentAV[68], currentAV[67], currentAV[66], currentAV[65], currentAV[64], currentAV[63], currentAV[62], currentAV[61], currentAV[60], currentAV[59], currentAV[58], currentAV[57], currentAV[56],
			currentAV[55], currentAV[54], currentAV[53], currentAV[52], currentAV[51], currentAV[50], currentAV[49], currentAV[48], currentAV[47], currentAV[46], currentAV[45], currentAV[44], currentAV[43], currentAV[42],
			currentAV[41], currentAV[40], currentAV[39], currentAV[38], currentAV[37], currentAV[36], currentAV[35], currentAV[34], currentAV[33], currentAV[32], currentAV[31], currentAV[30], currentAV[29], currentAV[28],
			currentAV[27], currentAV[26], currentAV[25], currentAV[24], currentAV[23], currentAV[22], currentAV[21], currentAV[20], currentAV[19], currentAV[18], currentAV[17], currentAV[16], currentAV[15], currentAV[14],
			currentAV[13], currentAV[12], currentAV[11], currentAV[10], currentAV[9], currentAV[8], currentAV[7], currentAV[6], currentAV[5], currentAV[4], currentAV[3], currentAV[2], currentAV[1], currentAV[0]
				])

		identities.append((GameState(currentBoard, state.playerTurn), currentAV))

		return identities


class GameState():
	def __init__(self, board, playerTurn):
		self.board = board
		self.pieces = {'1':'X', '0': '-', '-1':'O'}
		self.playerTurn = playerTurn
		self.binary = self._binary()
		self.id = self._convertStateToId()
		self.allowedActions = self._allowedActions()
		self.playerWon = 0
		self.isEndGame = self._checkForEndGame()
		self.value = self._getValue()
		self.score = self._getScore()
		

	def _allowedActions(self):
		return np.where(self.board == 0)[0]

	def _binary(self):

		currentplayer_position = np.zeros(len(self.board), dtype=np.int)
		currentplayer_position[self.board==self.playerTurn] = 1

		other_position = np.zeros(len(self.board), dtype=np.int)
		other_position[self.board==-self.playerTurn] = 1

		position = np.append(currentplayer_position,other_position)

		return (position)

	def _convertStateToId(self):
		player1_position = np.zeros(len(self.board), dtype=np.int)
		player1_position[self.board==1] = 1

		other_position = np.zeros(len(self.board), dtype=np.int)
		other_position[self.board==-1] = 1

		position = np.append(player1_position,other_position)

		id = ''.join(map(str,position))

		return id

	def _checkForEndGame(self):
		it = 0
		visited = []
		for value in self.board:
			if it in visited or value == 0:
				it += 1
				continue
			unvisited = deque([it])
			hastop = 0
			hasdown = 0
			hasri = 0
			hasleft = 0
			while unvisited:
				visiting = unvisited.popleft();
				i = int(visiting / 14);
				j = visiting % 14;
				if (j - 1 >= 0 and visiting - 1 not in visited and value == self.board[visiting-1]):
					unvisited.append(visiting-1)
					
				if (j + 1 < 14 and visiting + 1 not in visited and value == self.board[visiting+1]):
					unvisited.append(visiting+1)
				
				if (i - 1 >= 0 and visiting - 14 not in visited and value == self.board[visiting-14]):
					unvisited.append(visiting-14)
					
				if (i + 1 < 14 and visiting + 14 not in visited and value == self.board[visiting+14]):
					unvisited.append(visiting+14)
				
				visited.append(visiting)
				if i == 0:
					hastop = 1
				elif i == 13:
					hasdown = 1
				if j == 13:
					hasleft = 1
				elif j == 0:
					hasri = 1
			
			if (hastop and hasdown and value == 1):
				self.playerWon = 1
				return 1
			elif (hasleft and hasri and value == -1):
				self.playerWon = -1
				return 1
			it += 1
		return 0


	def _getValue(self):
		# This is the value of the state for the current player
		# i.e. if the previous player played a winning move, you lose
		if(self.playerWon == -self.playerTurn):
			return (-1, -1, 1)
		return (0, 0, 0)


	def _getScore(self):
		tmp = self.value
		return (tmp[1], tmp[2])

	def takeAction(self, action):
		newBoard = np.array(self.board)
		newBoard[action]=self.playerTurn
		newState = GameState(newBoard, -self.playerTurn)

		value = 0
		done = 0

		if newState.isEndGame:
			value = newState.value[0]
			done = 1

		return (newState, value, done)

	def render(self, logger):
		for r in range(14):
			logger.info([self.pieces[str(x)] for x in self.board[14*r : (14*r + 14)]])
		logger.info('--------------')



