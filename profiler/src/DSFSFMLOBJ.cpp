//
//  DSFSFMLOBJ.cpp
//  profiler
//
//  Created by Yu Chen on 2/17/15.
//
//

#include "../include/DSFSFMLOBJ.h"

DSFSFMLOBJ::DSFSFMLOBJ()
{
    this->Create = new dsf::TaskFunction([this](dsf::SynchronizedObject* to,
                                               dsf::SynchronizedObject* from,
                                               dsf::TaskArgument* args)
                                        {
                                            dsf::DualStateFramework* dsf;
                                            bool* create;
                                            bool* update;
                                            dsf::TaskArgument*
                                            std::tie(dsf, create, update) = args->to<std::tuple<dsf::DualStateFramework*, bool*, bool*>>();
                                            if(*create)
                                            {
                                                this->create(to, from, args);
                                                dsf->send(to, from, this->Update, args);
                                            }
                                            else
                                            {
                                                dsf->remove(to);
                                            }
                                        });
    this->Update = new dsf::TaskFunction([this](dsf::SynchronizedObject* to,
                                                dsf::SynchronizedObject* from,
                                                dsf::TaskArgument* args)
                                         {
                                             bool* create;
                                             bool* update;
                                             dsf::DualStateFramework* dsf;
                                             std::tie(dsf, create, update) = args->to<std::tuple<dsf::DualStateFramework*, bool*, bool*>>();
                                             if(*update)
                                             {
                                                 this->update(to, from, args);
                                                 dsf->send(to, from, this->Update, args);
                                             }
                                             else
                                             {
                                                 this->destroy(to, from, args);
                                                 dsf->remove(to);
                                             }
                                             
                                         });
}

DSFSFMLOBJ::~DSFSFMLOBJ()
{
    delete this->Create;
    delete this->Update;
}
