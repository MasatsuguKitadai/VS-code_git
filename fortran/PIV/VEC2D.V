// MicroAVS Application: 5.00
// Date: 23 1ŒŽ 2004 03:32:26
// DataNames: 1 vectors_fld
// BitField: 0
// Methods: 1 7
// Actives: 1	 FLDVector1D
// Comments:  
// End
MicroAVS.MicroAVS MicroAVS {
   MicroAVS.MAviewer3D MAviewer {
      viewer_params {
         renderer = 1;
         top_xform {
            ocenter = {0.08191,0.0759865,
0.};
            dcenter = {3.50681,-5.05274,
0.};
         };
      };
      objs_in => {
         MAviewerEditors.label_objs,<-.FLDVector1D.obj_out};
      MAviewerEditors {
         TransformEditor {
            MAGDxform_sub_obj {
               MAGDxform_save_mdl {
                  &Xform;
               };
               MAGDxform_update_mdl {
                  &Xform;
               };
            };
         };
      };
      MAviewer3Editors {
         AxisGraphEditor {
            Params {
               axis_editor_params {
                  axis1 {
                     start = -0.4898880124;
                     end = 0.6523119807;
                     step = 0.2284399986;
                  };
                  axis2 {
                     start = -0.4886240065;
                     end = 0.6418839693;
                     step = 0.2261015952;
                  };
                  axis3 {
                     start = -0.5;
                     end = 0.5;
                     step = 0.2;
                  };
               };
            };
         };
      };
   };
   MicroAVS.MAfieldReader vectors_fld {
      Params {
         field_params {
            each_values = {
               {
                  max_value=0.0007239999832,,min_value=-0.0006321999826,,,
               },
               {
                  max_value=0.000731099979,,min_value=-0.0007318999851,,,
               }};
            all_min_value = -0.0007318999851;
            all_max_value = 0.000731099979;
            crop_dwn_set = 1;
         };
      };
      filename = "G:\\MIYAZAKI\\vectors.fld";
   };
   MicroAVS.field_networks.FLDVector1D FLDVector1D<NEvisible=1> {
      Params {
         colmap_params {
            curmin = 0.0004232208012;
            curmax = 0.0009068557993;
            min_col_val = 0.0004232208012;
            max_col_val = 0.0009068557993;
         };
         vector_params {
            scale = 10.;
            normalize = 0;
         };
         downsize_params {
            downsize = 1;
            max = 85;
         };
      };
      UI {
         MAcombine_vectUI {
            comb_vect_opt_UI {
               label_cmd {
                  cmd[];
               };
            };
         };
      };
      fld_in => <-.vectors_fld.field;
      in_pick => <-.MAviewer.picked_obj;
   };
};
MicroAVS.MAviewer.viewer_params.auto_norm = 0;// Auto Normalize Off
