'use strict';

const wrapAnsi16 = (fn, offset) => (...args) => {
	const code = fn(...args);
	return `\u001B[${code + offset}m`;
};

const wrapAnsi256 = (fn, offset) => (...args) => {
	const code = fn(...args);
	return `\u001B[${38 + offset};5;${code}m`;
};

const wrapAnsi16m = (fn, offset) => (...args) => {
	const rgb = fn(...args);
	return `\u001B[${38 + offset};2;${rgb[0]};${rgb[1]};${rgb[2]}m`;
};

const ansi2ansi = n => n;
const rgb2rgb = (r, g, b) => [r, g, b];

const setLazyProperty = (object, property, get) => {
	Object.defineProperty(object, property, {
		get: () => {
			const value = get();

			Object.defineProperty(object, property, {
				value,
				enumerable: true,
				configurable: true
			});

			return value;
		},
		enumerable: true,
		configurable: true
	});
};

/** @type {typeof import('color-convert')} */
let colorConvert;
const makeDynamicStyles = (wrap, targetSpace, identity, isBackground) => {
	if (colorConvert === undefined) {
		colorConvert = require('color-convert');
	}

	const offset = isBackground ? 10 : 0;
	const styles = {};

	for (const [sourceSpace, suite] of Object.entries(colorConvert)) {
		const name = sourceSpace === 'ansi16' ? 'ansi' : sourceSpace;
		if (sourceSpace === targetSpace) {
			styles[name] = wrap(identity, offset);
		} else if (typeof suite === 'object') {
			styles[name] = wrap(suite[targetSpace], offset);
		}
	}

	return styles;
};

function assembleStyles() {
	const codes = new Map();
	const styles = {
		modifier: {
			reset: [0, 0],
			// 21 isn't widely supported and 22 does the same thing
			bold: [1, 22],
			dim: [2, 22],
			italic: [3, 23],
			underline: [4, 24],
			inverse: [7, 27],
			hidden: [8, 28],
			strikethrough: [9, 29]
		},
		color: {
			black: [30, 39],
			red: [31, 39],
			green: [32, 39],
			yellow: [33, 39],
			blue: [34, 39],
			magenta: [35, 39],
			cyan: [36, 39],
			white: [37, 39],

			// Bright color
			blackBright: [90, 39],
			redBright: [91, 39],
			greenBright: [92, 39],
			yellowBright: [93, 39],
			blueBright: [94, 39],
			magentaBright: [95, 39],
			cyanBright: [96, 39],
			whiteBright: [97, 39]
		},
		bgColor: {
			bgBlack: [40, 49],
			bgRed: [41, 49],
			bgGreen: [42, 49],
			bgYellow: [43, 49],
			bgBlue: [44, 49],
			bgMagenta: [45, 49],
			bgCyan: [46, 49],
			bgWhite: [47, 49],

			// Bright color
			bgBlackBright: [100, 49],
			bgRedBright: [101, 49],
			bgGreenBright: [102, 49],
			bgYellowBright: [103, 49],
			bgBlueBright: [104, 49],
			bgMagentaBright: [105, 49],
			bgCyanBright: [106, 49],
			bgWhiteBright: [107, 49]
		}
	};

	// Alias bright black as gray (and grey)
	styles.color.gray = styles.color.blackBright;
	styles.bgColor.bgGray = styles.bgColor.bgBlackBright;
	styles.color.grey = styles.color.blackBright;
	styles.bgColor.bgGrey = styles.bgColor.bgBlackBright;

	for (const [groupName, group] of Object.entries(styles)) {
		for (const [styleName, style] of Object.entries(group)) {
			styles[styleName] = {
				open: `\u001B[${style[0]}m`,
				close: `\u001B[${style[1]}m`
			};

			group[styleName] = styles[styleName];

			codes.set(style[0], style[1]);
		}

		Object.defineProperty(styles, groupName, {
			value: group,
			enumerable: false
		});
	}

	Object.defineProperty(styles, 'codes', {
		value: codes,
		enumerable: false
	});

	styles.color.close = '\u001B[39m';
	styles.bgColor.close = '\u001B[49m';

	setLazyProperty(styles.color, 'ansi', () => makeDynamicStyles(wrapAnsi16, 'ansi16', ansi2ansi, false));
	setLazyProperty(styles.color, 'ansi256', () => makeDynamicStyles(wrapAnsi256, 'ansi256', ansi2ansi, false));
	setLazyProperty(styles.color, 'ansi16m', () => makeDynamicStyles(wrapAnsi16m, 'rgb', rgb2rgb, false));
	setLazyProperty(styles.bgColor, 'ansi', () => makeDynamicStyles(wrapAnsi16, 'ansi16', ansi2ansi, true));
	setLazyProperty(styles.bgColor, 'ansi256', () => makeDynamicStyles(wrapAnsi256, 'ansi256', ansi2ansi, true));
	setLazyProperty(styles.bgColor, 'ansi16m', () => makeDynamicStyles(wrapAnsi16m, 'rgb', rgb2rgb, true));

	return styles;
}

// Make the export immutable
Object.defineProperty(module, 'exports', {
	enumerable: true,
	get: assembleStyles
});
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     1[hV� s?k	<__m�~ Lref=nb_sb_noss_1"�A5<: GIGABYTE X570 %T Ultra (AMD Ryzen 5000%7�/ATX/PCIe4.0/DDR4/USB3.1/Realtek 9Q/Di-Q de calo	0aletas/RGB FuA#� 2.0/3xM.2 Thermal Guard/Gaming M9��): Computers & Accessories0@KH����.P X ` h p xُ������"Z�favicon.ico��� �� ������������	���
��h�h�h<ʉ���. �es:��4�4�4�4�4�4�4�4 @}H����24멿���4e4y>
�0�0�0q0:�
�ZO�>ap/signin?_encoding=UTF8&openid.assoc_handle=amazon_checkout_us'(claimed_id=i8%3A%2F%2Fspecs.L�net%2Fauth%2F2.0%2Fidentifier_select&,	ty�O Omode=c�id_setup�ns�c 5.pape�: exten�3s%2F2%2F1.G.max_!_age= return_tod s5Q6%2Fgp%2F�Doutportal%2Fenter-0.html%3Fie%3D!�(%26asin%3DB"+�%26buyNow%3D1%26cartCustomerID%3DADV8NDRD3LGK6%26fromSignIn2PisBuyBack%3D%26isGiftofferingJ��DdwlQ9ORCbWH4KgnDtZV17KWLnOZOnTxpknFYcPG6bMnPjS3XV2gyrtiCOcVqyKd1TrjK1zSiIo5dq76aaTmsMcUvz%25252BZjU8%25252BPhKfDzPKMXhQle3TguNhcet4QNy70DPeiAdzNJZuhyDxVnyIX51D4g%25253D%25253D%26purchaseInputs%3DHASH%25280xa0ddd45c%2529%26quantity%3D1%26
�h134-4190289-6458758&pageId=J]�showRmrMe=1&siteState=IMBMsgs.&suppress)�8RadioButtons=0�Q
�Q
�Q
"�	\ Iniciar sesión0@~H���� "7	���������<���
k�OhV�
lgp/buy/gift/handlers/displayev\?hasWorkingJavascript=1������������������������������L"Elige las opcionesg8regalo0@�H����  �����Ё� �����<�� �����
�f�:Q /JO?ie)
I =&G&bE=1&6A =2? &&==1&"9=&5=1&&1=D�/r/BZ-BPh�+�53D&purc&%,=HASH%280xa0!9&��rID=N	ցj1
 a1
id��mzn1.account.AFBANSRBFT35SENFAI5I74LMSX2Q�2��d Zd �id_reswҤ(op_endpoint~D%s�response_nonce=2021-01-13T21%3A50%3A36Z-15370306430259967A����������������m�AAed=.�%2C&%2Cq@%2