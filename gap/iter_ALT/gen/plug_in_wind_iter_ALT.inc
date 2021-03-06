/* ----------------------------------------------------------------------
 * p_plug_in_wind_iter_ALT 
 * ----------------------------------------------------------------------
 */
gint p_plug_in_wind_iter_ALT(GimpRunMode run_mode, gint32 total_steps, gdouble current_step, gint32 len_struct) 
{
    typedef enum
    {
      LEFT,
      RIGHT
    } t_wind_direction;

    typedef enum
    {
      RENDER_WIND,
      RENDER_BLAST
    } t_wind_algorithm;

    typedef enum
    {
      BOTH,
      LEADING,
      TRAILING
    } t_wind_edge;


    typedef struct t_plug_in_wind_Vals 
    {
      gint                  threshold;
      t_wind_direction      direction;
      gint                  strength;
      t_wind_algorithm      alg;
      t_wind_edge           edge;
    } t_plug_in_wind_Vals; 

    t_plug_in_wind_Vals  buf, *buf_from, *buf_to; 

    if(len_struct != sizeof(t_plug_in_wind_Vals)) 
    {
      fprintf(stderr, "ERROR: p_plug_in_wind_iter_ALT  stored Data missmatch in size %d != %d\n",   
                       (int)len_struct, sizeof(t_plug_in_wind_Vals) ); 
      return -1;  /* ERROR */ 
    }

    gimp_get_data("plug-in-wind-ITER-FROM", g_plugin_data_from); 
    gimp_get_data("plug-in-wind-ITER-TO",   g_plugin_data_to); 

    buf_from = (t_plug_in_wind_Vals *)&g_plugin_data_from[0]; 
    buf_to   = (t_plug_in_wind_Vals *)&g_plugin_data_to[0]; 
    memcpy(&buf, buf_from, sizeof(buf));

    p_delta_gint(&buf.threshold, buf_from->threshold, buf_to->threshold, total_steps, current_step);
    p_delta_gint(&buf.strength, buf_from->strength, buf_to->strength, total_steps, current_step);

    gimp_set_data("plug-in-wind", &buf, sizeof(buf)); 

    return 0; /* OK */
}
