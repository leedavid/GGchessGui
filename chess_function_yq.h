
//extern void yq_add_moves               (list_t * list, const board_t * board);
//extern void yq_add_captures            (list_t * list, const board_t * board);
//extern void yq_add_quiet_moves         (list_t * list, const board_t * board);
//extern bool yq_list_contain 		   (const list_t *list, mv_t move);
//extern void yq_add_promotes            (list_t * list, const board_t * board);
//extern void yq_add_en_passant_captures (list_t * list, const board_t * board);
//extern void yq_add_castle_moves        (list_t * list, const board_t * board);
//extern bool yq_move_is_pseudo_debug(mv_t move, board_t * board);
//extern void	yq_gen_quiet_checks      (list_t * list, board_t * board);
//extern bool	yq_move_is_check         (int move, board_t * board);
//extern void yq_move_do        (board_t * board, mv_t move, undo_t * undo);
//extern void yq_move_undo      (board_t * board, mv_t move, const undo_t * undo);
//extern void yq_move_do_null   (board_t * board, undo_t * undo);
//extern void yq_move_undo_null (board_t * board, const undo_t * undo);
//extern void yq_gen_legal_evasions  (list_t * list, const board_t * board, const attack_t * attack);
//extern void yq_gen_pseudo_evasions (list_t * list, const board_t * board, const attack_t * attack);
//extern bool yq_legal_evasion_exist (const board_t * board, const attack_t * attack);
//extern void yq_gen_legal_moves (list_t * list, board_t * board);
//extern void yq_gen_moves       (list_t * list, const board_t * board);
//extern void yq_gen_captures    (list_t * list, const board_t * board);
//extern void yq_gen_quiet_moves (list_t * list, const board_t * board);
//extern bool yq_move_is_pseudo  (mv_t move, board_t * board);
//extern bool yq_quiet_is_pseudo (mv_t move, board_t * board);
//extern bool yq_pseudo_is_legal (mv_t move, board_t * board);
//
//extern bool yq_move_is_ok            (mv_t move);
//extern mv_t yq_move_promote          (mv_t move);
//extern mv_t yq_move_order            (mv_t move);
//extern bool yq_move_is_capture       (mv_t move, const board_t * board);
//extern bool yq_move_is_under_promote (mv_t move);
//extern bool yq_move_is_tactical      (mv_t move, const board_t * board);
//extern int  yq_move_capture          (mv_t move, const board_t * board);
//extern void yq_move_do_init   ();
//
//extern bool yq_list_is_ok    (const list_t * list);
//extern void yq_list_remove   (list_t * list, int pos);
//extern void yq_list_copy     (list_t * dst, const list_t * src);
//extern void yq_list_sort     (list_t * list);
//
//extern void yq_list_note     (list_t * list);
//extern void yq_list_filter   (list_t * list, board_t * board, move_test_t test, bool keep);
