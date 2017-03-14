#!/bin/bash

YEL="\033[33m"
GREEN="\033[32m"
RED="\033[31m"
RES="\033[0m"
INT_MAX="2147483647"
INT_MIN="-2147483648"


lm_test() { 
	echo -e "\n$YEL"$1"$RES";
	echo -e $2 | ./lem_in;
}

lm_test_verif() { 
	echo -e "\n$YEL"$1"$RES";
	echo -e $2 | ./lem_in;
	RET=`echo -e $2 | ./lem_in | grep -e "\(L[0-9]+\).*\1"`;
	if [[ $RET ]]; then
		echo -e "$RED""\nSAME ANT ON THE SAME LINE"
		echo -e "\nERROR : ""$RET";
	fi
	RET=`echo -e $2 | ./lem_in | grep -e "-\(.*\) .*\1"`;
	if [[ $RET ]]; then
		echo -e "$RED""\nSAME ROOM ON THE SAME LINE"
		echo -e "\nERROR : ""$RET";
	fi
}

lm_test_e() { 
	echo -e "\n$YEL"$1"$RES";
	WCL=`echo -e $2 | ./lem_in | grep L | wc -l`;
	echo $WCL "steps on" $3 "steps mini."
}

display_title() {
	echo -e "\n=============================="
	echo -e "== $GREEN""  Lem_in parsing tests$RES   =="
	echo -e "==============================\n"
}

correction_tests() {
	echo -e "$GREEN""42 CORRECTION TESTS$RES"

	lm_test  \
		"Test 00: no rooms" \
		"10\n" 
	lm_test  \
		"Test 01: no ants" \
		"room1 1 1\n"
	lm_test  \
		"Test 02a: no ##end / no ##start" \
		"10\nroom1 1 1\nroom2 2 2\nroom3 3 3\nroom1-room2"
	lm_test  \
		"Test 02b: no ##start" \
		"10\nroom1 1 1\nroom2 2 2\n##end\nroom3 3 3\nroom1-room2"
	lm_test  \
		"Test 02c: no ##end" \
		"10\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\nroom1-room2"
	lm_test  \
		"Test 03: no valid path" \
		"10\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\nroom3-room2"
	lm_test  \
		"Test 04: valid colony with comments" \
		"10\n##this is a comment\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\n#this is another comment\nroom3-room2\nroom2-room1"
	lm_test  \
		"Test 05: valid colony with other commands" \
		"10\n##command1\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\n##command2\nroom3-room2\nroom2-room1"
	lm_test  \
		"Test 06: valid input display output format" \
		"10\n##end\nroom1 1 1\nroom2 2 2\n##start\nroom3 3 3\n#what a great output !\nroom3-room2\nroom2-room1"
	lm_test  \
		"Test 07: Demonstrating shortest path" \
		"1\n##start\nr0 1 1\nr1 1 1\nr2 1 1\nr3 1 1\n##end\nr4 1 1\nr5 1 1\nr6 1 1\nr7 1 1\nr0-r1\nr0-r5\nr1-r2\nr1-r7\nr2-r3\nr3-r4\nr4-r7\nr7-r6\nr6-r5"
	lm_test_verif  \
		"Test 08: Multiple ants" \
		"10\n##start\nr0 1 1\nr1 1 1\nr2 1 1\nr3 1 1\n##end\nr4 1 1\nr5 1 1\nr6 1 1\nr7 1 1\nr0-r1\nr0-r5\nr1-r2\nr1-r7\nr2-r3\nr3-r4\nr4-r7\nr7-r6\nr6-r5"
}

ants_parsing() {
	echo -e "$GREEN""ANTS PARSING$RES"

	lm_test  \
		"Test 00: 0 ants" \
		"0" 
	lm_test  \
		"Test 01: -10 ants" \
		"-10"
	lm_test  \
		"Test 02: INT_MAX ants" \
		"$INT_MAX"
}

rooms_parsing() {
	echo -e "$GREEN""\nROOMS PARSING$RES"

	lm_test  \
		"Test 00: 10 ants, no room" \
		"10"
	lm_test  \
		"Test 01: 0 room" \
		"10\n2-3"
	lm_test  \
		"Test 02: 0 room, 3 comments" \
		"10\n#comment\n##comment\n###comment\n3-4"
	lm_test  \
		"Test 03: invalid room format 1 (L)$" \
		"10\n#comment\n##start\nroom1 2 3\nLroom2 9 1\n3-4"
	lm_test  \
		"Test 04: invalid room format 2 (name x y z)" \
		"10\n#comment\n##start\nroom1 2 3 4\nLroom2 9 1\n3-4" 
	lm_test  \
		"Test 05: invalid room format 3 (name x)" \
		"10\n#comment\n##start\nroom1 4\nLroom2 9 1\n3-4"
	lm_test  \
		"Test 06: invalid room format 4 (wrong x y)" \
		"10\n#comment\n##start\nroom1 4 3\nLroom2 a b\n3-4"
	lm_test  \
		"Test 07: invalid room format 5 (name only)" \
		"10\n#comment\n##start\nroom1\nLroom2 a b\n3-4"
	lm_test  \
		"Test 08: ##start && ##end attributed to the same room" \
		"10\n#comment\n##end\n##start\nroom1 4 3\nroom2 4 99\n3-4"
	lm_test  \
		"Test 09: valid room format" \
		"10\n#comment\n##start\nroom1 4 3\nroom2 4 99\n3-4"
	# INT MAX coordinates
}

edges_parsing() {
	echo -e "$GREEN""\nEDGES PARSING$RES"

	lm_test  \
		"Test 00: no edges" \
		"10\n#comment\n##start\nroom1 4 3\n##end\nroom2 4 99"
	lm_test  \
		"Test 01: normal edges" \
		"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3\nr3-r1"
	lm_test  \
		"Test 02: double dash - -" \
		"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3-\nr3-r1"
	lm_test  \
		"Test 03: triple dash - - -" \
		"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3--\nr3-r1"
	lm_test  \
		"Test 04: circular edge roomA-roomA" \
		"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r1\nr2-r3\nr3-r1"
	lm_test  \
		"Test 05: non-existing room in edge" \
		"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr2-r3\nr2-r9\nr3-r1"
	lm_test  \
		"Test 06: triple rooms" \
		"10\n#comment\n##start\nr1 4 3\nr3 0 9\n##end\nr2 4 99\nr1-r2\nr2-r3-r1\nr3-r1"
	# tirets "-" "- -" "--"
}


efficiency() {
	echo -e "$GREEN""\nEFFICIENCY$RES"

	lm_test_e  \
		"Test 00: multi-path" \
		"12\n##start\n1 23 3\n2 16 7\n3 16 3\n4 16 5\n5 0 0\n6 0 0\n##end\n0 9 5\n1-2\n1-3\n1-4\n1-5\n1-6\n2-0\n3-0\n4-0\n5-0\n6-0" \
		"4"
	lm_test_e  \
		"Test 00: multi-path + anti-bfs" \
		"50\n##start\n1 23 3\n2 16 7\n#commentaire\n3 16 3\n4 16 5\n5 9 3\n6 1 5\n7 4 8\n##end\n8 9 5\n1-2\n2-3\n3-4\n4-8\n1-5\n5-6\n6-7\n7-2\n7-8" \
		"28"
	lm_test_e  \
		"Test 00: multi-path + anti-//" \
		"3\n##start\n1 23 3\n2 16 7\n#commentaire\n3 16 3\n4 16 5\n5 9 3\n6 1 5\n7 4 8\n##end\n8 9 5\n1-2\n2-3\n3-4\n4-8\n1-5\n5-6\n6-7\n7-2\n7-8" \
		"5"
	lm_test_e  \
		"Test 00: multi-path + anti-dfs" \
		"100\n##start\nstart 0 1\n##end\nend 1 0\n0 0 0\n1 1 1\n2 2 2\n3 3 3\n4 4 4\n5 5 5\n6 6 6\n7 7 7\n8 8 8\n9 9 9\n10 10 10\n11 11 11\n12 12 12\n13 13 13\n14 14 14\n15 15 15\n16 16 16\n17 17 17\n18 18 18\n19 19 19\n20 20 20\n21 21 21\n22 22 22\n23 23 23\n24 24 24\n25 25 25\n26 26 26\n27 27 27\n28 28 28\n29 29 29\n30 30 30\n31 31 31\n32 32 32\n33 33 33\n34 34 34\n35 35 35\n36 36 36\n37 37 37\n38 38 38\n39 39 39\n40 40 40\n41 41 41\n42 42 42\n43 43 43\n44 44 44\n45 45 45\n46 46 46\n47 47 47\n48 48 48\n49 49 49\n50 50 50\n51 51 51\n52 52 52\n53 53 53\n54 54 54\n55 55 55\n56 56 56\n57 57 57\n58 58 58\n59 59 59\n60 60 60\n61 61 61\n62 62 62\n63 63 63\n64 64 64\n65 65 65\n66 66 66\n67 67 67\n68 68 68\n69 69 69\n70 70 70\n71 71 71\n72 72 72\n73 73 73\n74 74 74\n75 75 75\n76 76 76\n77 77 77\n78 78 78\n79 79 79\n80 80 80\n81 81 81\n82 82 82\n83 83 83\n84 84 84\n85 85 85\n86 86 86\n87 87 87\n88 88 88\n89 89 89\n90 90 90\n91 91 91\n92 92 92\n93 93 93\n94 94 94\n95 95 95\n96 96 96\n97 97 97\n98 98 98\n99 99 99\n100 100 100\n101 101 101\n102 102 102\n103 103 103\n104 104 104\n105 105 105\n106 106 106\n107 107 107\n108 108 108\n109 109 109\n110 110 110\n111 111 111\n112 112 112\n113 113 113\n114 114 114\n115 115 115\n116 116 116\n117 117 117\n118 118 118\n119 119 119\n120 120 120\n121 121 121\n122 122 122\n123 123 123\n124 124 124\n125 125 125\n126 126 126\n127 127 127\n128 128 128\n129 129 129\n130 130 130\n131 131 131\n132 132 132\n133 133 133\n134 134 134\n135 135 135\n136 136 136\n137 137 137\n138 138 138\n139 139 139\n140 140 140\n141 141 141\n142 142 142\n143 143 143\n144 144 144\n145 145 145\n146 146 146\n147 147 147\n148 148 148\n149 149 149\n150 150 150\n151 151 151\n152 152 152\n153 153 153\n154 154 154\n155 155 155\n156 156 156\n157 157 157\n158 158 158\n159 159 159\n160 160 160\n161 161 161\n162 162 162\n163 163 163\n164 164 164\n165 165 165\n166 166 166\n167 167 167\n168 168 168\n169 169 169\n170 170 170\n171 171 171\n172 172 172\n173 173 173\n174 174 174\n175 175 175\n176 176 176\n177 177 177\n178 178 178\n179 179 179\n180 180 180\n181 181 181\n182 182 182\n183 183 183\n184 184 184\n185 185 185\n186 186 186\n187 187 187\n188 188 188\n189 189 189\n190 190 190\n191 191 191\n192 192 192\n193 193 193\n194 194 194\n195 195 195\n196 196 196\n197 197 197\n198 198 198\n199 199 199\n200 200 200\n201 201 201\n202 202 202\n203 203 203\n204 204 204\n205 205 205\n206 206 206\n207 207 207\n208 208 208\n209 209 209\n210 210 210\n211 211 211\n212 212 212\n213 213 213\n214 214 214\n215 215 215\n216 216 216\n217 217 217\n218 218 218\n219 219 219\n220 220 220\n221 221 221\n222 222 222\n223 223 223\n224 224 224\n225 225 225\n226 226 226\n227 227 227\n228 228 228\n229 229 229\n230 230 230\n231 231 231\n232 232 232\n233 233 233\n234 234 234\n235 235 235\n236 236 236\n237 237 237\n238 238 238\n239 239 239\n240 240 240\n241 241 241\n242 242 242\n243 243 243\n244 244 244\n245 245 245\n246 246 246\n247 247 247\n248 248 248\n249 249 249\n250 250 250\n251 251 251\n252 252 252\n253 253 253\n254 254 254\n255 255 255\n256 256 256\n257 257 257\n258 258 258\n259 259 259\n260 260 260\n261 261 261\n262 262 262\n263 263 263\n264 264 264\n265 265 265\n266 266 266\n267 267 267\n268 268 268\n269 269 269\n270 270 270\n271 271 271\n272 272 272\n273 273 273\n274 274 274\n275 275 275\n276 276 276\n277 277 277\n278 278 278\n279 279 279\n280 280 280\n281 281 281\n282 282 282\n283 283 283\n284 284 284\n285 285 285\n286 286 286\n287 287 287\n288 288 288\n289 289 289\n290 290 290\n291 291 291\n292 292 292\n293 293 293\n294 294 294\n295 295 295\n296 296 296\n297 297 297\n298 298 298\n299 299 299\n300 300 300\n301 301 301\n302 302 302\n303 303 303\n304 304 304\n305 305 305\n306 306 306\n307 307 307\n308 308 308\n309 309 309\n310 310 310\n311 311 311\n312 312 312\n313 313 313\n314 314 314\n315 315 315\n316 316 316\n317 317 317\n318 318 318\n319 319 319\n320 320 320\n321 321 321\n322 322 322\n323 323 323\n324 324 324\n325 325 325\n326 326 326\n327 327 327\n328 328 328\n329 329 329\n330 330 330\n331 331 331\n332 332 332\n333 333 333\n334 334 334\n335 335 335\n336 336 336\n337 337 337\n338 338 338\n339 339 339\n340 340 340\n341 341 341\n342 342 342\n343 343 343\n344 344 344\n345 345 345\n346 346 346\n347 347 347\n348 348 348\n349 349 349\n350 350 350\n351 351 351\n352 352 352\n353 353 353\n354 354 354\n355 355 355\n356 356 356\n357 357 357\n358 358 358\n359 359 359\n360 360 360\n361 361 361\n362 362 362\n363 363 363\n364 364 364\n365 365 365\n366 366 366\n367 367 367\n368 368 368\n369 369 369\n370 370 370\n371 371 371\n372 372 372\n373 373 373\n374 374 374\n375 375 375\n376 376 376\n377 377 377\n378 378 378\n379 379 379\n380 380 380\n381 381 381\n382 382 382\n383 383 383\n384 384 384\n385 385 385\n386 386 386\n387 387 387\n388 388 388\n389 389 389\n390 390 390\n391 391 391\n392 392 392\n393 393 393\n394 394 394\n395 395 395\n396 396 396\n397 397 397\n398 398 398\n399 399 399\n400 400 400\n401 401 401\n402 402 402\n403 403 403\n404 404 404\n405 405 405\n406 406 406\n407 407 407\n408 408 408\n409 409 409\n410 410 410\n411 411 411\n412 412 412\n413 413 413\n414 414 414\n415 415 415\n416 416 416\n417 417 417\n418 418 418\n419 419 419\n420 420 420\n421 421 421\n422 422 422\n423 423 423\n424 424 424\n425 425 425\n426 426 426\n427 427 427\n428 428 428\n429 429 429\n430 430 430\n431 431 431\n432 432 432\n433 433 433\n434 434 434\n435 435 435\n436 436 436\n437 437 437\n438 438 438\n439 439 439\n440 440 440\n441 441 441\n442 442 442\n443 443 443\n444 444 444\n445 445 445\n446 446 446\n447 447 447\n448 448 448\n449 449 449\n450 450 450\n451 451 451\n452 452 452\n453 453 453\n454 454 454\n455 455 455\n456 456 456\n457 457 457\n458 458 458\n459 459 459\n460 460 460\n461 461 461\n462 462 462\n463 463 463\n464 464 464\n465 465 465\n466 466 466\n467 467 467\n468 468 468\n469 469 469\n470 470 470\n471 471 471\n472 472 472\n473 473 473\n474 474 474\n475 475 475\n476 476 476\n477 477 477\n478 478 478\n479 479 479\n480 480 480\n481 481 481\n482 482 482\n483 483 483\n484 484 484\n485 485 485\n486 486 486\n487 487 487\n488 488 488\n489 489 489\n490 490 490\n491 491 491\n492 492 492\n493 493 493\n494 494 494\n495 495 495\n496 496 496\n497 497 497\n498 498 498\n499 499 499\n500 500 500\n501 501 501\n502 502 502\n503 503 503\n504 504 504\n505 505 505\n506 506 506\n507 507 507\n508 508 508\n509 509 509\n510 510 510\n511 511 511\n512 512 512\n513 513 513\n514 514 514\n515 515 515\n516 516 516\n517 517 517\n518 518 518\n519 519 519\n520 520 520\n521 521 521\n522 522 522\n523 523 523\n524 524 524\n525 525 525\n526 526 526\n527 527 527\n528 528 528\n529 529 529\n530 530 530\n531 531 531\n532 532 532\n533 533 533\n534 534 534\n535 535 535\n536 536 536\n537 537 537\n538 538 538\n539 539 539\n540 540 540\n541 541 541\n542 542 542\n543 543 543\n544 544 544\n545 545 545\n546 546 546\n547 547 547\n548 548 548\n549 549 549\n550 550 550\n551 551 551\n552 552 552\n553 553 553\n554 554 554\n555 555 555\n556 556 556\n557 557 557\n558 558 558\n559 559 559\n560 560 560\n561 561 561\n562 562 562\n563 563 563\n564 564 564\n565 565 565\n566 566 566\n567 567 567\n568 568 568\n569 569 569\n570 570 570\n571 571 571\n572 572 572\n573 573 573\n574 574 574\n575 575 575\n576 576 576\n577 577 577\n578 578 578\n579 579 579\n580 580 580\n581 581 581\n582 582 582\n583 583 583\n584 584 584\n585 585 585\n586 586 586\n587 587 587\n588 588 588\n589 589 589\n590 590 590\n591 591 591\n592 592 592\n593 593 593\n594 594 594\n595 595 595\n596 596 596\n597 597 597\n598 598 598\n599 599 599\n600 600 600\n601 601 601\n602 602 602\n603 603 603\n604 604 604\n605 605 605\n606 606 606\n607 607 607\n608 608 608\n609 609 609\n610 610 610\n611 611 611\n612 612 612\n613 613 613\n614 614 614\n615 615 615\n616 616 616\n617 617 617\n618 618 618\n619 619 619\n620 620 620\n621 621 621\n622 622 622\n623 623 623\n624 624 624\n625 625 625\n626 626 626\n627 627 627\n628 628 628\n629 629 629\n630 630 630\n631 631 631\n632 632 632\n633 633 633\n634 634 634\n635 635 635\n636 636 636\n637 637 637\n638 638 638\n639 639 639\n640 640 640\n641 641 641\n642 642 642\n643 643 643\n644 644 644\n645 645 645\n646 646 646\n647 647 647\n648 648 648\n649 649 649\n650 650 650\n651 651 651\n652 652 652\n653 653 653\n654 654 654\n655 655 655\n656 656 656\n657 657 657\n658 658 658\n659 659 659\n660 660 660\n661 661 661\n662 662 662\n663 663 663\n664 664 664\n665 665 665\n666 666 666\n667 667 667\n668 668 668\n669 669 669\n670 670 670\n671 671 671\n672 672 672\n673 673 673\n674 674 674\n675 675 675\n676 676 676\n677 677 677\n678 678 678\n679 679 679\n680 680 680\n681 681 681\n682 682 682\n683 683 683\n684 684 684\n685 685 685\n686 686 686\n687 687 687\n688 688 688\n689 689 689\n690 690 690\n691 691 691\n692 692 692\n693 693 693\n694 694 694\n695 695 695\n696 696 696\n697 697 697\n698 698 698\n699 699 699\n700 700 700\n701 701 701\n702 702 702\n703 703 703\n704 704 704\n705 705 705\n706 706 706\n707 707 707\n708 708 708\n709 709 709\n710 710 710\n711 711 711\n712 712 712\n713 713 713\n714 714 714\n715 715 715\n716 716 716\n717 717 717\n718 718 718\n719 719 719\n720 720 720\n721 721 721\n722 722 722\n723 723 723\n724 724 724\n725 725 725\n726 726 726\n727 727 727\n728 728 728\n729 729 729\n730 730 730\n731 731 731\n732 732 732\n733 733 733\n734 734 734\n735 735 735\n736 736 736\n737 737 737\n738 738 738\n739 739 739\n740 740 740\n741 741 741\n742 742 742\n743 743 743\n744 744 744\n745 745 745\n746 746 746\n747 747 747\n748 748 748\n749 749 749\n750 750 750\n751 751 751\n752 752 752\n753 753 753\n754 754 754\n755 755 755\n756 756 756\n757 757 757\n758 758 758\n759 759 759\n760 760 760\n761 761 761\n762 762 762\n763 763 763\n764 764 764\n765 765 765\n766 766 766\n767 767 767\n768 768 768\n769 769 769\n770 770 770\n771 771 771\n772 772 772\n773 773 773\n774 774 774\n775 775 775\n776 776 776\n777 777 777\n778 778 778\n779 779 779\n780 780 780\n781 781 781\n782 782 782\n783 783 783\n784 784 784\n785 785 785\n786 786 786\n787 787 787\n788 788 788\n789 789 789\n790 790 790\n791 791 791\n792 792 792\n793 793 793\n794 794 794\n795 795 795\n796 796 796\n797 797 797\n798 798 798\n799 799 799\n800 800 800\n801 801 801\n802 802 802\n803 803 803\n804 804 804\n805 805 805\n806 806 806\n807 807 807\n808 808 808\n809 809 809\n810 810 810\n811 811 811\n812 812 812\n813 813 813\n814 814 814\n815 815 815\n816 816 816\n817 817 817\n818 818 818\n819 819 819\n820 820 820\n821 821 821\n822 822 822\n823 823 823\n824 824 824\n825 825 825\n826 826 826\n827 827 827\n828 828 828\n829 829 829\n830 830 830\n831 831 831\n832 832 832\n833 833 833\n834 834 834\n835 835 835\n836 836 836\n837 837 837\n838 838 838\n839 839 839\n840 840 840\n841 841 841\n842 842 842\n843 843 843\n844 844 844\n845 845 845\n846 846 846\n847 847 847\n848 848 848\n849 849 849\n850 850 850\n851 851 851\n852 852 852\n853 853 853\n854 854 854\n855 855 855\n856 856 856\n857 857 857\n858 858 858\n859 859 859\n860 860 860\n861 861 861\n862 862 862\n863 863 863\n864 864 864\n865 865 865\n866 866 866\n867 867 867\n868 868 868\n869 869 869\n870 870 870\n871 871 871\n872 872 872\n873 873 873\n874 874 874\n875 875 875\n876 876 876\n877 877 877\n878 878 878\n879 879 879\n880 880 880\n881 881 881\n882 882 882\n883 883 883\n884 884 884\n885 885 885\n886 886 886\n887 887 887\n888 888 888\n889 889 889\n890 890 890\n891 891 891\n892 892 892\n893 893 893\n894 894 894\n895 895 895\n896 896 896\n897 897 897\n898 898 898\n899 899 899\n900 900 900\n901 901 901\n902 902 902\n903 903 903\n904 904 904\n905 905 905\n906 906 906\n907 907 907\n908 908 908\n909 909 909\n910 910 910\n911 911 911\n912 912 912\n913 913 913\n914 914 914\n915 915 915\n916 916 916\n917 917 917\n918 918 918\n919 919 919\n920 920 920\n921 921 921\n922 922 922\n923 923 923\n924 924 924\n925 925 925\n926 926 926\n927 927 927\n928 928 928\n929 929 929\n930 930 930\n931 931 931\n932 932 932\n933 933 933\n934 934 934\n935 935 935\n936 936 936\n937 937 937\n938 938 938\n939 939 939\n940 940 940\n941 941 941\n942 942 942\n943 943 943\n944 944 944\n945 945 945\n946 946 946\n947 947 947\n948 948 948\n949 949 949\n950 950 950\n951 951 951\n952 952 952\n953 953 953\n954 954 954\n955 955 955\n956 956 956\n957 957 957\n958 958 958\n959 959 959\n960 960 960\n961 961 961\n962 962 962\n963 963 963\n964 964 964\n965 965 965\n966 966 966\n967 967 967\n968 968 968\n969 969 969\n970 970 970\n971 971 971\n972 972 972\n973 973 973\n974 974 974\n975 975 975\n976 976 976\n977 977 977\n978 978 978\n979 979 979\n980 980 980\n981 981 981\n982 982 982\n983 983 983\n984 984 984\n985 985 985\n986 986 986\n987 987 987\n988 988 988\n989 989 989\n990 990 990\n991 991 991\n992 992 992\n993 993 993\n994 994 994\n995 995 995\n996 996 996\n997 997 997\n998 998 998\n999 999 999\n0-542\n0-111\n1-971\n1-79\n2-818\n2-738\n2-291\n3-707\n4-532\n5-58\n6-492\n6-414\n6-748\n7-870\n8-440\n9-970\n9-381\n10-284\n11-588\n11-878\n11-416\n12-440\n12-179\n13-457\n14-346\n15-663\n15-784\n15-306\n16-699\n17-592\n18-508\n18-432\n19-639\n20-800\n21-835\n21-712\n22-34\n23-83\n24-540\n25-9\n26-419\n27-962\n27-116\n27-845\n28-206\n29-739\n30-681\n31-186\n32-260\n32-310\n32-501\n32-787\n32-852\n33-4\n33-655\n34-63\n34-806\n34-905\n35-228\n36-206\n36-632\n37-698\n38-778\n39-155\n39-690\n39-660\n40-605\n41-829\n41-981\n41-437\n41-33\n41-81\n42-356\n43-367\n44-457\n45-243\n46-740\n46-254\n46-196\n47-754\n48-363\n49-61\n50-634\n51-550\n51-917\n52-316\n53-750\n54-325\n55-533\n55-603\n56-939\n57-412\n57-293\n57-554\n57-70\n57-2\n57-527\n57-433\n57-299\n57-61\n57-162\n57-726\n57-413\n58-27\n58-770\n59-97\n59-226\n60-609\n61-52\n62-421\n62-198\n62-368\n62-177\n62-716\n63-179\n63-678\n64-503\n64-691\n65-163\n66-9\n66-69\n66-455\n66-25\n66-785\n66-958\n66-977\n66-413\n66-136\n67-770\n67-275\n67-41\n67-608\n68-116\n68-643\n69-20\n69-866\n70-723\n70-63\n71-906\n72-113\n73-390\n73-686\n74-772\n74-909\n74-800\n74-996\n74-191\n74-698\n74-519\n74-786\n74-713\n74-781\n75-37\n76-635\n77-728\n77-494\n77-55\n77-268\n78-231\n78-895\n78-844\n78-842\n78-154\n79-502\n79-252\n79-212\n80-802\n80-552\n81-228\n82-240\n82-103\n83-567\n83-954\n83-294\n83-750\n83-814\n83-661\n83-986\n84-323\n85-504\n85-737\n86-535\n87-441\n88-948\n89-716\n90-55\n91-487\n92-121\n93-611\n93-949\n93-2\n93-787\n93-171\n93-424\n94-577\n95-149\n95-542\n96-707\n96-434\n97-810\n97-774\n98-996\n98-415\n98-172\n99-897\n99-713\n99-737\n100-743\n101-283\n101-273\n102-158\n102-842\n103-209\n103-740\n103-113\n103-114\n103-721\n104-920\n104-693\n104-309\n104-746\n105-901\n106-205\n107-400\n108-126\n109-741\n110-539\n110-980\n111-501\n112-923\n112-743\n112-944\n113-350\n113-491\n114-226\n115-176\n115-769\n115-295\n116-7\n117-701\n117-37\n117-595\n118-795\n119-61\n120-692\n121-332\n121-407\n121-67\n122-286\n122-564\n123-907\n123-706\n124-67\n124-928\n125-970\n126-940\n126-969\n126-934\n126-761\n126-198\n126-819\n127-879\n127-837\n128-496\n128-303\n129-377\n129-854\n130-456\n130-490\n130-393\n131-800\n132-949\n132-582\n132-364\n132-852\n133-794\n134-792\n135-937\n136-191\n136-769\n136-186\n136-471\n137-719\n137-111\n137-858\n137-86\n137-584\n138-931\n139-260\n140-387\n140-293\n140-808\n141-108\n142-466\n143-478\n143-317\n143-152\n144-463\n144-159\n144-247\n144-721\n145-233\n145-99\n146-238\n146-358\n146-926\n146-934\n147-344\n148-242\n148-66\n149-45\n150-34\n151-498\n152-477\n152-404\n153-791\n154-163\n154-144\n154-757\n154-974\n154-406\n155-580\n156-94\n156-838\n157-405\n158-201\n159-917\n159-238\n159-631\n159-498\n160-936\n160-683\n160-313\n161-14\n162-228\n163-832\n163-466\n163-117\n164-303\n165-837\n165-465\n166-360\n167-824\n167-749\n167-803\n168-556\n168-521\n169-211\n170-15\n171-280\n171-580\n171-665\n171-882\n172-158\n173-980\n173-150\n174-29\n174-10\n174-199\n175-232\n175-314\n176-163\n177-380\n177-764\n178-867\n178-616\n179-939\n180-691\n180-633\n181-763\n181-117\n181-266\n181-604\n182-103\n182-439\n183-44\n183-451\n184-503\n185-513\n186-231\n187-459\n188-223\n189-685\n190-454\n190-387\n190-959\n191-791\n192-727\n193-94\n194-828\n194-64\n195-462\n195-410\n195-363\n195-972\n196-133\n196-182\n196-314\n196-365\n196-503\n197-413\n198-635\n198-425\n199-357\n200-384\n201-996\n201-95\n201-307\n201-15\n201-969\n201-85\n202-690\n202-253\n203-33\n203-20\n204-771\n205-900\n205-474\n206-634\n207-73\n208-671\n208-230\n208-488\n209-536\n210-948\n211-885\n212-766\n212-654\n213-181\n213-512\n213-447\n214-553\n215-473\n215-946\n216-115\n216-985\n217-755\n217-371\n217-897\n217-304\n218-722\n218-721\n218-505\n218-273\n219-145\n219-868\n220-397\n221-883\n221-734\n222-413\n223-417\n224-985\n225-382\n225-528\n225-673\n226-789\n226-702\n226-790\n227-124\n228-286\n229-684\n229-540\n230-760\n231-822\n231-335\n232-201\n232-284\n232-10\n232-594\n232-512\n232-974\n233-502\n234-991\n235-806\n235-587\n235-98\n235-637\n235-569\n236-605\n237-686\n238-47\n238-835\n239-918\n239-599\n239-297\n239-562\n239-742\n240-211\n240-452\n240-846\n241-853\n241-75\n242-906\n242-838\n243-78\n243-454\n244-911\n245-322\n246-671\n246-463\n247-989\n247-654\n248-203\n249-74\n249-752\n250-443\n250-485\n251-279\n252-205\n253-632\n254-669\n254-641\n254-484\n255-872\n255-250\n256-539\n257-754\n258-633\n259-302\n260-29\n261-501\n261-450\n261-892\n262-168\n262-15\n262-295\n262-665\n263-862\n264-627\n265-798\n266-602\n266-479\n267-105\n267-434\n267-762\n268-846\n269-989\n270-701\n270-334\n270-793\n270-836\n270-52\n271-432\n272-546\n272-871\n273-995\n273-201\n274-165\n275-78\n276-238\n277-390\n277-917\n277-657\n277-147\n277-555\n277-397\n278-6\n278-339\n278-297\n278-917\n278-137\n279-811\n279-850\n279-960\n280-312\n280-531\n280-409\n280-320\n280-757\n281-376\n282-777\n282-58\n283-584\n284-978\n284-471\n285-854\n286-507\n287-97\n288-365\n289-345\n290-975\n291-545\n292-6\n292-331\n292-86\n292-971\n293-850\n293-740\n294-499\n295-480\n295-311\n296-441\n297-211\n297-765\n297-62\n298-965\n298-370\n299-290\n299-165\n300-58\n301-262\n301-7\n302-904\n303-282\n304-951\n304-366\n305-136\n306-637\n307-256\n307-224\n308-804\n309-461\n310-862\n311-928\n312-883\n312-177\n313-735\n313-398\n314-391\n315-415\n316-892\n316-483\n316-482\n317-1\n317-344\n318-486\n318-289\n319-35\n320-376\n321-607\n322-738\n322-804\n323-920\n323-533\n324-592\n324-99\n325-626\n325-137\n325-462\n326-12\n326-170\n326-705\n326-122\n326-72\n326-737\n327-403\n328-587\n329-461\n329-809\n330-247\n330-425\n331-129\n332-331\n332-757\n332-80\n332-536\n333-471\n333-246\n333-773\n333-285\n333-566\n333-62\n333-986\n334-227\n335-742\n336-335\n336-560\n336-700\n337-372\n338-189\n339-181\n339-386\n340-875\n341-256\n341-151\n341-564\n341-248\n341-586\n342-395\n343-450\n344-796\n344-348\n344-739\n344-268\n344-208\n344-894\n344-180\n345-405\n345-727\n346-137\n347-523\n348-408\n348-547\n349-530\n349-484\n350-801\n350-344\n350-191\n351-921\n351-161\n352-328\n352-648\n352-600\n353-952\n353-334\n353-411\n354-413\n354-694\n354-476\n354-74\n354-215\n354-620\n355-721\n355-79\n355-398\n355-154\n356-911\n357-453\n357-191\n358-954\n358-379\n358-110\n359-774\n360-84\n361-775\n361-520\n362-719\n363-230\n364-780\n364-105\n364-217\n365-569\n365-118\n366-203\n366-945\n367-710\n368-745\n368-452\n369-435\n369-391\n369-165\n370-528\n371-705\n371-168\n372-635\n373-12\n373-500\n374-952\n374-967\n375-524\n376-117\n376-749\n377-708\n377-957\n377-567\n378-381\n379-251\n380-382\n380-338\n381-441\n381-861\n382-252\n382-408\n383-318\n383-335\n383-677\n383-954\n383-348\n383-761\n384-642\n385-581\n385-591\n386-368\n386-737\n386-779\n386-230\n386-272\n386-564\n387-288\n388-813\n389-18\n389-852\n389-458\n390-678\n391-157\n391-591\n392-702\n393-127\n394-348\n394-86\n395-660\n396-187\n397-41\n398-609\n398-302\n399-342\n400-186\n400-148\n400-84\n401-727\n401-346\n402-724\n402-85\n403-205\n404-172\n405-995\n406-284\n407-584\n408-745\n408-370\n408-283\n408-86\n408-615\n409-846\n409-472\n410-619\n410-916\n411-777\n412-707\n412-57\n413-640\n414-315\n415-433\n416-901\n417-805\n418-578\n418-458\n419-215\n420-70\n421-994\n421-160\n421-612\n422-385\n423-527\n423-299\n423-387\n424-875\n424-782\n424-679\n425-823\n426-796\n426-975\n427-846\n427-300\n427-210\n427-529\n427-117\n428-104\n429-400\n429-184\n429-833\n429-180\n429-692\n429-593\n430-389\n431-508\n432-812\n433-917\n433-574\n434-299\n434-466\n435-683\n436-690\n437-286\n437-918\n437-726\n437-616\n438-932\n439-390\n440-122\n440-593\n441-890\n442-922\n442-434\n442-35\n442-699\n442-776\n442-41\n443-244\n443-203\n443-923\n444-353\n444-372\n445-881\n446-163\n446-516\n446-902\n447-751\n447-983\n447-308\n447-992\n447-970\n448-427\n448-422\n448-503\n449-60\n450-38\n450-186\n451-94\n452-781\n452-718\n452-194\n452-400\n453-700\n454-163\n454-432\n455-99\n455-874\n455-115\n455-356\n456-131\n456-592\n457-300\n458-547\n458-502\n459-405\n459-619\n459-315\n459-168\n459-320\n459-850\n459-109\n459-806\n459-212\n460-702\n460-610\n461-857\n462-11\n463-299\n464-226\n465-423\n466-359\n467-66\n468-544\n469-791\n469-421\n470-359\n470-60\n470-473\n470-527\n471-489\n472-136\n472-294\n472-365\n472-631\n472-597\n473-683\n473-705\n473-235\n474-196\n474-580\n474-480\n475-464\n476-726\n476-224\n477-831\n477-146\n477-751\n478-862\n479-466\n479-994\n480-478\n481-915\n482-514\n482-926\n482-485\n483-522\n483-520\n483-309\n483-600\n483-356\n484-444\n484-883\n485-419\n485-604\n486-960\n486-424\n487-91\n487-318\n488-784\n488-445\n488-387\n488-449\n489-980\n489-934\n490-775\n491-946\n492-633\n493-193\n493-373\n494-957\n495-1\n495-776\n495-375\n495-140\n495-176\n496-295\n497-529\n498-350\n498-672\n499-678\n499-385\n499-872\n499-136\n499-167\n499-657\n499-503\n499-216\n499-554\n500-374\n501-947\n502-402\n502-491\n502-643\n503-855\n504-886\n504-502\n505-226\n506-559\n506-752\n506-140\n506-129\n506-156\n507-116\n507-366\n508-280\n508-449\n508-679\n509-879\n510-302\n511-769\n511-997\n512-837\n512-358\n512-997\n512-392\n512-159\n513-886\n514-166\n515-49\n515-245\n515-204\n516-668\n517-540\n517-701\n518-464\n518-409\n519-400\n520-428\n521-65\n521-297\n521-799\n522-879\n523-690\n523-629\n523-751\n523-702\n524-332\n525-626\n526-704\n527-180\n527-81\n527-383\n528-829\n528-664\n529-604\n529-304\n529-589\n530-747\n531-974\n531-337\n532-376\n532-492\n533-946\n534-701\n535-91\n536-162\n536-514\n537-419\n537-857\n538-609\n538-960\n539-848\n540-94\n541-136\n542-895\n542-948\n542-594\n543-835\n543-174\n543-710\n544-835\n545-568\n546-190\n547-910\n548-352\n548-647\n548-209\n549-365\n550-113\n550-601\n550-446\n550-815\n551-998\n552-450\n552-108\n553-57\n553-376\n553-829\n553-770\n553-520\n554-761\n554-479\n554-142\n554-876\n554-34\n555-999\n556-314\n557-862\n558-994\n558-14\n558-845\n559-516\n560-386\n561-585\n561-439\n561-19\n562-951\n562-715\n562-33\n562-471\n563-122\n564-276\n565-728\n565-151\n566-496\n566-185\n566-856\n566-733\n566-993\n566-135\n567-765\n567-840\n568-502\n568-511\n568-531\n568-131\n568-93\n568-819\n569-47\n569-151\n570-850\n570-123\n571-997\n571-408\n571-360\n572-839\n573-975\n574-107\n575-829\n575-337\n576-628\n576-824\n577-784\n578-230\n578-371\n578-463\n578-56\n579-173\n579-724\n579-196\n579-296\n580-712\n580-815\n580-681\n580-371\n580-570\n581-595\n582-986\n583-36\n584-934\n585-879\n586-784\n587-570\n587-98\n587-532\n587-371\n587-254\n588-392\n589-684\n589-87\n589-578\n589-948\n589-515\n590-418\n590-80\n591-774\n592-225\n592-440\n592-685\n593-423\n594-125\n594-36\n594-684\n595-207\n596-778\n596-708\n596-60\n597-95\n597-809\n597-19\n598-946\n599-60\n600-97\n600-481\n600-567\n600-16\n600-450\n600-615\n601-401\n602-331\n602-87\n602-304\n602-390\n603-835\n604-841\n604-698\n604-717\n605-940\n605-102\n605-257\n606-316\n606-861\n607-384\n608-175\n608-986\n609-638\n609-542\n609-278\n609-193\n610-921\n610-981\n611-170\n611-10\n612-328\n613-492\n614-954\n615-839\n616-924\n617-771\n617-227\n618-204\n619-993\n619-510\n620-362\n621-161\n622-940\n622-543\n623-678\n623-882\n623-144\n623-802\n623-701\n623-829\n623-895\n624-735\n624-759\n625-151\n625-695\n626-559\n627-762\n627-794\n628-542\n629-141\n630-335\n630-419\n631-520\n631-598\n631-104\n632-292\n632-203\n632-528\n632-596\n632-119\n632-909\n633-556\n633-940\n633-767\n633-358\n633-393\n634-597\n635-898\n636-817\n636-718\n637-403\n638-93\n638-564\n638-14\n638-313\n639-290\n639-74\n640-115\n640-839\n640-801\n641-913\n641-871\n641-97\n641-210\n641-564\n642-916\n642-30\n643-596\n644-978\n645-724\n645-432\n646-717\n647-927\n647-631\n647-462\n648-61\n649-165\n649-368\n649-260\n650-142\n650-804\n651-238\n652-886\n652-953\n653-409\n654-211\n654-745\n655-251\n656-896\n656-794\n657-953\n658-793\n659-802\n659-534\n659-68\n659-648\n660-844\n661-125\n661-147\n661-326\n661-536\n662-146\n663-447\n664-359\n664-72\n665-229\n665-389\n666-743\n667-182\n667-330\n667-812\n667-540\n667-92\n668-798\n669-583\n670-844\n670-624\n671-833\n671-151\n671-76\n671-756\n672-153\n673-977\n673-730\n673-207\n673-394\n674-421\n675-737\n675-962\n675-590\n675-964\n676-892\n676-60\n677-232\n677-718\n677-342\n678-30\n678-777\n678-886\n679-961\n679-978\n680-441\n681-755\n681-737\n682-697\n682-829\n682-378\n683-966\n684-405\n685-405\n685-631\n685-703\n685-560\n685-638\n685-843\n685-411\n685-806\n685-291\n685-758\n686-287\n687-933\n687-139\n688-555\n688-760\n688-830\n689-922\n690-979\n690-177\n690-556\n691-534\n691-989\n692-19\n693-505\n693-155\n694-0\n695-322\n695-332\n695-371\n695-440\n696-165\n696-694\n696-157\n697-767\n697-923\n697-527\n697-742\n697-610\n698-564\n698-770\n698-453\n698-934\n699-299\n699-372\n700-278\n700-187\n700-84\n700-579\n701-495\n701-656\n701-395\n702-784\n702-691\n703-501\n704-179\n705-276\n705-984\n705-93\n705-233\n706-790\n707-98\n707-319\n708-493\n709-718\n709-796\n709-142\n710-881\n711-790\n711-11\n712-101\n713-577\n713-772\n713-821\n713-488\n714-593\n715-769\n716-891\n717-545\n718-737\n718-918\n718-161\n719-594\n720-950\n720-739\n720-964\n720-672\n721-973\n721-192\n722-193\n722-210\n722-276\n723-100\n723-745\n723-707\n723-355\n723-747\n724-283\n725-654\n726-656\n726-743\n726-466\n726-396\n726-503\n727-273\n727-685\n727-233\n727-818\n728-101\n728-472\n729-104\n730-280\n730-618\n731-505\n732-989\n732-854\n733-679\n733-48\n734-937\n734-164\n735-200\n736-909\n737-332\n737-885\n737-287\n738-473\n739-605\n740-500\n741-776\n742-103\n742-900\n742-559\n742-811\n743-677\n743-337\n744-9\n745-456\n745-331\n745-749\n746-219\n746-122\n747-798\n748-447\n748-272\n748-742\n748-448\n748-898\n748-766\n748-380\n749-841\n749-461\n750-383\n750-833\n750-361\n751-27\n752-899\n752-501\n752-441\n753-552\n754-794\n755-726\n756-101\n756-999\n756-211\n756-888\n756-525\n757-370\n758-411\n759-826\n759-366\n759-496\n759-408\n759-156\n759-969\n759-28\n760-68\n761-188\n762-317\n763-161\n763-822\n764-531\n764-97\n765-444\n766-944\n767-958\n767-953\n768-458\n769-486\n770-419\n770-688\n770-798\n770-413\n771-299\n772-658\n773-557\n774-199\n774-598\n775-76\n775-617\n776-804\n776-892\n776-357\n776-680\n777-153\n777-346\n777-394\n778-103\n778-479\n779-943\n780-323\n781-655\n781-93\n781-538\n781-322\n782-349\n782-804\n782-427\n782-610\n782-251\n783-944\n784-942\n785-567\n785-564\n786-246\n786-722\n786-841\n787-835\n788-56\n788-326\n788-886\n788-315\n788-762\n788-725\n788-864\n789-547\n789-780\n790-536\n791-869\n791-568\n792-593\n793-628\n793-902\n794-972\n794-585\n795-603\n796-898\n796-889\n797-855\n798-609\n799-258\n799-420\n799-335\n799-739\n800-65\n800-345\n800-104\n801-969\n801-689\n801-786\n802-472\n803-530\n803-958\n803-510\n804-987\n804-617\n804-400\n805-227\n805-690\n805-191\n805-14\n805-420\n806-108\n807-931\n807-907\n808-788\n808-160\n808-108\n809-789\n809-709\n809-782\n809-962\n810-358\n811-999\n812-936\n812-445\n812-820\n812-195\n812-14\n813-249\n813-139\n814-21\n814-536\n815-708\n816-720\n816-815\n816-60\n816-444\n817-754\n818-408\n818-420\n819-101\n819-345\n820-416\n820-13\n821-619\n822-688\n822-17\n822-538\n822-52\n822-886\n823-61\n824-898\n825-843\n825-552\n826-496\n827-410\n827-127\n828-107\n829-190\n830-989\n830-562\n831-574\n831-721\n832-12\n833-742\n833-111\n834-657\n834-576\n834-486\n834-557\n834-331\n834-92\n835-870\n836-157\n837-577\n837-186\n838-255\n839-309\n839-835\n840-917\n841-832\n841-756\n842-371\n843-569\n843-977\n843-249\n844-998\n844-314\n844-729\n845-258\n846-676\n846-726\n847-421\n847-954\n847-420\n848-845\n848-810\n848-63\n849-771\n849-978\n849-904\n849-565\n850-441\n851-404\n852-128\n853-946\n853-129\n854-18\n855-159\n855-498\n856-26\n857-449\n857-660\n858-896\n858-333\n859-866\n859-241\n859-97\n860-806\n860-398\n861-331\n862-178\n863-597\n864-385\n864-172\n865-772\n866-711\n866-275\n867-654\n867-73\n867-246\n867-850\n868-319\n869-247\n869-914\n869-327\n870-128\n870-860\n870-380\n871-604\n872-441\n872-550\n873-86\n874-732\n875-343\n876-436\n876-775\n876-430\n876-222\n877-76\n878-473\n879-881\n880-109\n881-319\n882-62\n883-973\n884-138\n884-730\n884-778\n885-893\n886-191\n886-234\n887-461\n888-478\n888-678\n888-514\n888-619\n889-165\n889-544\n889-114\n890-877\n891-874\n892-132\n893-346\n894-733\n895-615\n895-217\n896-670\n897-227\n897-570\n898-923\n899-260\n900-378\n901-613\n901-620\n901-526\n902-241\n902-675\n903-603\n904-468\n904-820\n904-808\n904-934\n905-491\n905-65\n905-961\n906-638\n906-95\n906-611\n906-958\n906-410\n906-392\n906-186\n907-422\n907-130\n908-284\n909-326\n910-179\n910-637\n911-491\n912-496\n913-181\n914-619\n915-883\n916-720\n917-281\n918-993\n918-705\n918-713\n918-183\n919-98\n919-381\n919-25\n919-614\n919-635\n920-559\n920-508\n920-580\n920-47\n920-743\n921-389\n922-366\n922-113\n923-464\n923-187\n924-691\n925-760\n925-336\n926-129\n926-728\n927-73\n928-956\n929-147\n929-718\n930-678\n931-929\n932-789\n932-582\n933-56\n933-994\n934-734\n934-117\n934-144\n935-240\n935-674\n936-46\n936-921\n937-618\n938-650\n938-367\n938-876\n938-8\n938-288\n938-390\n939-398\n940-179\n941-185\n941-585\n942-443\n942-938\n943-291\n943-788\n944-856\n944-462\n945-368\n945-787\n945-933\n946-880\n947-489\n948-311\n948-86\n949-728\n949-353\n950-674\n950-983\n950-729\n950-898\n950-751\n951-47\n952-210\n953-202\n954-665\n955-672\n955-786\n955-236\n956-469\n957-854\n957-38\n958-431\n959-460\n959-754\n959-65\n959-230\n960-386\n960-232\n960-504\n960-571\n960-313\n960-26\n961-454\n961-453\n961-902\n962-212\n963-545\n964-972\n965-95\n966-939\n967-501\n968-416\n968-820\n968-457\n969-841\n970-371\n971-696\n971-688\n971-198\n972-765\n972-818\n973-563\n974-609\n975-587\n975-889\n975-633\n976-855\n977-113\n977-30\n977-185\n978-102\n978-362\n978-942\n979-667\n980-794\n980-987\n980-195\n981-658\n982-282\n983-243\n983-340\n984-164\n984-140\n984-265\n984-789\n984-86\n984-59\n984-939\n984-406\n985-511\n985-208\n985-786\n986-230\n987-843\n988-340\n988-786\n989-213\n990-882\n991-642\n992-713\n992-568\n993-671\n993-497\n993-982\n993-203\n993-881\n994-470\n994-167\n994-900\n995-147\n995-600\n995-623\n996-375\n996-629\n997-395\n997-674\n998-429\n999-462\nstart-99\nstart-806\nstart-49\nstart-843\nstart-960\nend-121\nend-563\nend-437" \
		"39"
}

main() {
	display_title
	correction_tests
#	ants_parsing
#	rooms_parsing
#	edges_parsing
#	efficiency
}

main $@
